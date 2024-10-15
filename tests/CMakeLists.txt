if (NOT BUILD_TESTS)
    return()
endif()

find_package(GTest REQUIRED)
enable_testing()

function(add_unit_test FILENAME_WITHOUT_CPP)
    add_executable(${FILENAME_WITHOUT_CPP} ${FILENAME_WITHOUT_CPP}.cpp)
    fsi_compile_options(${FILENAME_WITHOUT_CPP})
    target_link_libraries(${FILENAME_WITHOUT_CPP}
        PRIVATE
            fsi_lib
            pthread
            GTest::GTest
            GTest::Main
    )
    add_test(fsi_tests ${FILENAME_WITHOUT_CPP})
endfunction()

add_unit_test(test_function_traits)
add_unit_test(test_type_erasure)
