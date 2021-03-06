include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(2d_src
        ${CMAKE_CURRENT_SOURCE_DIR}/render/2d/pointmap.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/render/2d/general_2d.cpp
        render/2d/heatmap/heatmap.cpp
        render/2d/heatmap/set_color.cpp
        )
set(window_src
        ${CMAKE_CURRENT_SOURCE_DIR}/render/window/window2d.cpp
        )

if (USE_GPU)
    set(window_src render/window/window_egl/window_gpu_2d.cpp
            render/2d/cuda/heatmap.cu)
else ()
    set(window_src render/window/window_osmesa/window_cpu_2d.cpp)
endif ()

set(util_src
        ${CMAKE_CURRENT_SOURCE_DIR}/render/utils/vega/vega_scatter_plot/vega_circle2d.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/render/utils/vega/vega.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/render/utils/vega/vega_heatmap/vega_heatmap.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/render/utils/color/color.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/render/utils/color/color_gradient.cpp
        )
set(arrow_src
        arrow/render_api.cpp
        )

set(render_src
        ${2d_src}
        ${window_src}
        ${util_src}
        ${arrow_src}
        )

set(gis_src
        ${CMAKE_CURRENT_SOURCE_DIR}/gis/cpu/gdal_based_impl.cpp
        )

set(LIBRARY_TYPE SHARED)
if (STATIC_LIB_SWITCH)
    set(LIBRARY_TYPE STATIC)
endif (STATIC_LIB_SWITCH)

add_library(
    windrose ${LIBRARY_TYPE}
    ${render_src}
    ${gis_src}
)

add_dependencies(windrose miniz_ep stb_ep)

set_property(TARGET windrose PROPERTY CUDA_STANDARD 11)
if (USE_GPU)
    target_link_libraries(windrose
            GL
            EGL
            cudart
            arrow
            pthread
            miniz
            )
else ()
    target_link_libraries(windrose
            GLU
            OSMesa
	        gdal
            arrow
            pthread
            miniz
            )
endif ()


install(TARGETS windrose
        DESTINATION lib)

