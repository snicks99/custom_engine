#  Future problems
Overriding the global new & delete operator:
On Windows DLL not compiled by us can't be re-linked to use our global allocation system, so it can bring problems.
For example, if we try to delete memory not allocated by our system with our system, will crash. - niccco

