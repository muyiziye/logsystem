#!/bin/bash
########################################################################
# File Name: template.sh
# Author: LiuYang
# mail: liu-yang91@qq.com
# Created Time: Fri 19 Nov 2021 02:03:41 PM CST
#########################################################################

# define some environment value
BUILD_MODE=release
COMPILE_FLAGS=" -Wall -Werror "
OUTPUT_PATH=`pwd`"/build/${BUILD_MODE}_output_compile"
PRINT_CMD=False
CLEAN_CACHE=False
CMAKE_CMD="cmake"
SRC_PATH=`pwd`/src


# hand the options
usage="$ `basename $0`  <option> \n
\n
Options:\n
-d --debug\t\t\t\t Set debug mode, default is release.\n
-g --gcov\t\t\t\t Compile with gcov's options. Alway used in debug mode.\n
-a --asan\t\t\t\t Compile with asan's options. Alway used in debug mode.\n
-c --clean\t\t\t\t Clean all the compile cache(include build and output).\n
-p --print\t\t\t\t Just print the finally Make command.\n
-o --output <value>\t\t\t set the build output path\n
-t[only] --unittest[=only]\t\t compile unittest, only means just compile unittest\n
-h --help\t\t\t\t help message.\n
"

## handle parameters
OPTS=`getopt -o dgao:pct::h -l debug,gcov,asan,output:,print,clean,unittest:: -- "$@"`
if [ $? != 0 ]; then
    echo -ne $usage;
    exit 1
fi

eval set -- "$OPTS"
while true; do
    case $1 in
        -d|--debug)
			CMAKE_CMD="${CMAKE_CMD} -DDEBUG_MODE=ON "
            shift;
            continue
            ;;
        -g|--gcov)
			CMAKE_CMD="${CMAKE_CMD} -DENABLE_GCOV=ON "
            shift;
            continue
            ;;
        -a|--asan)
			CMAKE_CMD="${CMAKE_CMD} -DENABLE_ASAN=ON "
            shift;
            continue
            ;;
        -o|--output)
            echo "Set output path: $2" ; 
            OUTPUT_PATH=`realpath $2`
            shift 2;
            continue
            ;;
        -p|--print)
			PRINT_CMD=True
            shift;
            continue
            ;;
        -c|--clean)
			CLEAN_CACHE=True
            shift;
            continue
            ;;
        -t|--unittest)
            case $2 in
                "")
                    echo "compile with unittest";
                    shift 2
                    ;;
                *)
                    echo "can set param, param: $2"; 
					if [ x$2 == x"only" ]; then
						echo "only compile unittest"
					else
						echo "compile with unittest"
					fi
                    shift 2
                    ;;
            esac
            ;;
        -h|--help)
            echo -ne $usage;
             exit 0;;
        --)
            shift;
            break;;
        *)
            printf "Unknown option %s\n" "$1";
            break
    esac
done

if [ ${CLEAN_CACHE} == True ];then
    echo "Clean all the cache"
	rm -rf build
    exit 0 
fi

CMAKE_CMD="${CMAKE_CMD} -DOUTPUT_PATH=${OUTPUT_PATH}"

if [ ${PRINT_CMD} == True ];then
	echo "cd build; ${CMAKE_CMD} ${SRC_PATH}; make -j2"
else
	mkdir -pv build/${BUILD_MODE}_cache
    mkdir -pv ${OUTPUT_PATH}
	pushd build/${BUILD_MODE}_cache;
	${CMAKE_CMD} ${SRC_PATH};
	make -j2 install;
	popd
fi
	
