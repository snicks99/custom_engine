FROM debian:bullseye-20220125-slim

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update \
 && apt-get install --no-install-recommends -y \
    git clang cmake make gcc g++ libmariadbclient-dev-compat \
    libssl-dev libbz2-dev libreadline-dev libncurses-dev \
    libboost-all-dev p7zip default-libmysqlclient-dev \
 < /dev/null > /dev/null \
 && rm -rf /var/lib/apt/lists/* \
 && update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100 \
 && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang 100

#COPY . /dbosrv
RUN mkdir -pv /dbosrv/build/
WORKDIR /dbosrv/build/

#RUN cmake .. -DWITH_WARNINGS=0 -DDBO_CLIENT=0 -DDBO_TOOLS=0 -DDBO_SERVER=1 \
# && make


#CMD ["cmake", ".. -DWITH_WARNINGS=0 -DDBO_CLIENT=0 -DDBO_TOOLS=0 -DDBO_SERVER=1"]
#ENTRYPOINT [ "entrypoint.sh" ]