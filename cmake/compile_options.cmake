function(fsi_compile_options TARGET_NAME )
    # Set C++ standards
    target_compile_definitions(${TARGET_NAME} PRIVATE cxx_std_23)
    set_target_properties(${TARGET_NAME}
        PROPERTIES
            CXX_STANDARD_REQUIRED   ON
            CXX_EXTENSIONS          OFF
            LINKER_LANGUAGE         CXX
    )

    # Use ccache if available
    if (CCACHE_FOUND)
        set_target_properties(${TARGET_NAME}
            PROPERTIES
                CXX_COMPILER_LAUNCHER   ccache
        )
    endif(CCACHE_FOUND)

    # Set warnings
    target_compile_options(${TARGET_NAME}
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
    )

    # Set compile definitions
    target_compile_options(${TARGET_NAME}
        PRIVATE
            $<$<CONFIG:Debug>: -O0 -ggdb>
            $<$<CONFIG:RelWithDebInfo>: -O3 -g1>
    )

    # Other additional arguments
    target_compile_options(${TARGET_NAME} PRIVATE ${ARGN})
endfunction()
