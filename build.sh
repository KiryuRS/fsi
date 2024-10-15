#!/bin/bash

show_usage() {
    echo "$0 [-r|--rebuild] [-d|--debug] [-v|--verbose] [-t|--test]"
    exit 0
}

die() {
    echo -e "$1"
    exit 1
}

command_parser() {
    POSITIONAL_ARGS=()

    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                show_usage
                ;;
            -r|--rebuild)
                REBUILD=1
                shift # past argument
                ;;
            -d|--debug)
                CONFIG="Debug"
                shift # past argument
                ;;
            -v|--verbose)
                VERBOSE=1
                shift # past argument
                ;;
            -t|--test)
                BUILD_TESTS=1
                shift # past argument
                ;;
            -*|--*)
                die "Unknown option $1"
                ;;
            *)
                POSITIONAL_ARGS+=("$1") # Save positional arguments
                shift # past argument
                ;;
        esac
    done

    set -- "${POSITIONAL_ARGS[@]}" # restore positional parameters
}

main() {
    # Default arguments
    CONFIG="RelWithDebInfo"
    VERBOSE=0
    BUILD_DIR=$PWD/.build
    REBUILD=0
    BUILD_TESTS=0

    command_parser $@

    if [ $REBUILD -eq 1 ]; then
        echo "Deleting $BUILD_DIR ..."
        rm -rf $BUILD_DIR
    fi

    # Requirements prior to using conan:
    # Python >= 3.6
    # pip install conan
    # https://docs.conan.io/2/introduction.html
    conan install . --build=missing --output-folder=$BUILD_DIR --settings=build_type=$CONFIG

    local CONAN_CMAKE_TOOLCHAIN=$BUILD_DIR/build/$CONFIG/generators/conan_toolchain.cmake

    local EXTRA_BUILD_ARGS=
    if [ $BUILD_TESTS -eq 1 ]; then
        EXTRA_BUILD_ARGS+="-DBUILD_TESTS=ON "
    fi

    local EXTRA_CMAKE_ARGS=
    if [ $VERBOSE -eq 1 ]; then
        EXTRA_CMAKE_ARGS+="--verbose "
    fi

    pushd $BUILD_DIR > /dev/null
    cmake .. -DCMAKE_TOOLCHAIN_FILE=$CONAN_CMAKE_TOOLCHAIN -DCMAKE_BUILD_TYPE=$CONFIG $EXTRA_BUILD_ARGS
    cmake --build . $EXTRA_CMAKE_ARGS

    if [ $? -eq 0 ] && [ $BUILD_TESTS -eq 1 ]; then
        pushd $BUILD_DIR/tests > /dev/null

        echo "Build test detected, running unit tests"
        GTEST_COLOR=1 ctest --verbose

        popd > /dev/null
    fi

    popd > /dev/null
}

main $@
