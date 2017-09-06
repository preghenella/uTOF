UTOF_DIR=$(dirname $(readlink -e ${BASH_SOURCE[0]}))
export UTOF_ROOT=$UTOF_DIR
export PATH=$PATH:$UTOF_ROOT/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$UTOF_ROOT/lib
