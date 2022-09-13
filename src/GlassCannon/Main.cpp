/**
 * @file Main.cpp
 * @brief Authentication Server main program
 */

#include "Common/Platform.h"
#include "Debug/MGEAssert.h"
#include "Asio/DeadlineTimer.h"
#include "Asio/IoContext.h"
#include "Log/Logger.h"
#include "Configuration/Config.h"
#include "Threading/ProcessPriority.h"
#include "Server/AuthSocketMgr.h"
#include <boost/asio/signal_set.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <csignal>

Logger gLogger{ "authserver.txt" };

using boost::asio::ip::tcp;
using namespace boost::program_options;
namespace fs = boost::filesystem;

#define AUTHSERVER_CONFIG "authserver.conf"

#if MGE_PLATFORM == MGE_PLATFORM_WINDOWS
/*
 * -1 - not in service mode
 *  0 - stopped
 *  1 - running
 *  2 - paused
 */
int m_ServiceStatus = -1;

void ServiceStatusWatcher( std::weak_ptr<Trinity::Asio::DeadlineTimer> serviceStatusWatchTimerRef, std::weak_ptr<Trinity::Asio::IoContext> ioContextRef, boost::system::error_code const& error );
#endif

void SignalHandler( std::weak_ptr<Trinity::Asio::IoContext> ioContextRef, boost::system::error_code const& error, int signalNumber );

int main( int argc, char** argv )
{
    auto        configFile = fs::absolute( AUTHSERVER_CONFIG );
    std::string configError;
    if ( !sConfigMgr->LoadInitial( configFile.generic_string(),
                                   std::vector<std::string>( argv, argv + argc ),
                                   configError ) )
    {
        printf( "Error in config file: %s\n", configError.c_str() );
        return 1;
    }

    MGE_LOG( "Auth Server" );
    MGE_LOG( " ____    ____     _____   ____                    __             " );
    MGE_LOG( "/\\  _`\\ /\\  _`\\  /\\  __`\\/\\  _`\\                 /\\ \\__  __                     " );
    MGE_LOG( "\\ \\ \\/\\ \\ \\ \\L\\ \\\\ \\ \\/\\ \\ \\ \\/\\ \\     __    ____\\ \\ ,_\\/\\_\\    ___   __  __    " );
    MGE_LOG( " \\ \\ \\ \\ \\ \\  _ <'\\ \\ \\ \\ \\ \\ \\ \\ \\  /'__`\\ /',__\\\\ \\ \\/\\/\\ \\ /' _ `\\/\\ \\/\\ \\   " );
    MGE_LOG( "  \\ \\ \\_\\ \\ \\ \\L\\ \\\\ \\ \\_\\ \\ \\ \\_\\ \\/\\  __//\\__, `\\\\ \\ \\_\\ \\ \\/\\ \\/\\ \\ \\ \\_\\ \\  " );
    MGE_LOG( "   \\ \\____/\\ \\____/ \\ \\_____\\ \\____/\\ \\____\\/\\____/ \\ \\__\\\\ \\_\\ \\_\\ \\_\\/`____ \\ " );
    MGE_LOG( "    \\/___/  \\/___/   \\/_____/\\/___/  \\/____/\\/___/   \\/__/ \\/_/\\/_/\\/_/`/___/> \\" );
    MGE_LOG( "                                                    Based on Trinity-Core /\\___/" );
    MGE_LOG( "                                          Adapted to DBO by niccco & Xanu \\/__/ \n\n" );
    MGE_LOG( "Using configuration file %s.", sConfigMgr->GetFilename().c_str() );
    MGE_LOG( "Using Boost version: %i.%i.%i", BOOST_VERSION / 100000, BOOST_VERSION / 100 % 1000, BOOST_VERSION % 100 );

    std::shared_ptr<Trinity::Asio::IoContext> ioContext = std::make_shared<Trinity::Asio::IoContext>();

    // Start the listening port (acceptor) for auth connections
    int32 port = sConfigMgr->GetIntDefault( "AuthServerPort", 50200 );
    if ( port < 0 || port > 0xFFFF )
    {
        MGE_ERROR( "Specified port out of allowed range (1-65535)" );
        return 1;
    }

    std::string bindIp = sConfigMgr->GetStringDefault( "BindIP", "0.0.0.0" );

    if ( !sAuthSocketMgr.StartNetwork( *ioContext, bindIp, port ) )
    {
        MGE_ERROR( "Failed to initialize network" );
        return 1;
    }

    std::shared_ptr<void> sAuthSocketMgrHandle( nullptr, []( void* )
                                                { sAuthSocketMgr.StopNetwork(); } );

    // Set signal handlers
    boost::asio::signal_set signals( *ioContext, SIGINT, SIGTERM );
#if MGE_PLATFORM == MGE_PLATFORM_WINDOWS
    signals.add( SIGBREAK );
#endif
    signals.async_wait( std::bind( &SignalHandler, std::weak_ptr<Trinity::Asio::IoContext>( ioContext ), std::placeholders::_1, std::placeholders::_2 ) );

    // Set process priority according to configuration settings
    // SetProcessPriority( "server.authserver", sConfigMgr->GetIntDefault( CONFIG_PROCESSOR_AFFINITY, 0 ), sConfigMgr->GetBoolDefault( CONFIG_HIGH_PRIORITY, false ) );
    SetProcessPriority( "server.authserver", 0, false );

#if MGE_PLATFORM == MGE_PLATFORM_WINDOWS
    std::shared_ptr<Trinity::Asio::DeadlineTimer> serviceStatusWatchTimer;
    if ( m_ServiceStatus != -1 )
    {
        serviceStatusWatchTimer = std::make_shared<Trinity::Asio::DeadlineTimer>( *ioContext );
        serviceStatusWatchTimer->expires_from_now( boost::posix_time::seconds( 1 ) );
        serviceStatusWatchTimer->async_wait( std::bind( &ServiceStatusWatcher,
                                                        std::weak_ptr<Trinity::Asio::DeadlineTimer>( serviceStatusWatchTimer ),
                                                        std::weak_ptr<Trinity::Asio::IoContext>( ioContext ),
                                                        std::placeholders::_1 ) );
    }
#endif

    // Start the io service worker loop
    ioContext->run();

    MGE_LOG( "Halting process..." );

    signals.cancel();
}

void SignalHandler( std::weak_ptr<Trinity::Asio::IoContext> ioContextRef, boost::system::error_code const& error, int /*signalNumber*/ )
{
    if ( !error )
        if ( std::shared_ptr<Trinity::Asio::IoContext> ioContext = ioContextRef.lock() )
            ioContext->stop();
}

#if MGE_PLATFORM == MGE_PLATFORM_WINDOWS
void ServiceStatusWatcher( std::weak_ptr<Trinity::Asio::DeadlineTimer> serviceStatusWatchTimerRef, std::weak_ptr<Trinity::Asio::IoContext> ioContextRef, boost::system::error_code const& error )
{
    if ( !error )
    {
        if ( std::shared_ptr<Trinity::Asio::IoContext> ioContext = ioContextRef.lock() )
        {
            if ( m_ServiceStatus == 0 )
                ioContext->stop();
            else if ( std::shared_ptr<Trinity::Asio::DeadlineTimer> serviceStatusWatchTimer = serviceStatusWatchTimerRef.lock() )
            {
                serviceStatusWatchTimer->expires_from_now( boost::posix_time::seconds( 1 ) );
                serviceStatusWatchTimer->async_wait( std::bind( &ServiceStatusWatcher, serviceStatusWatchTimerRef, ioContextRef, std::placeholders::_1 ) );
            }
        }
    }
}
#endif
