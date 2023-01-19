#######################################
# Effect
find_package(PkgConfig)
pkg_check_modules(LCMS2 REQUIRED lcms2)
set_package_properties(LCMS2 PROPERTIES TYPE REQUIRED PURPOSE "Required for ICC color correction.")

set(icc_SOURCES icc.cpp icc.qrc main.cpp)
kconfig_add_kcfg_files(icc_SOURCES iccconfig.kcfgc)
kwin_add_builtin_effect(icc ${icc_SOURCES})
target_link_libraries(icc PRIVATE
    kwin
    KF6::ConfigGui
    ${LCMS2_LIBRARIES}
)
target_include_directories(icc PUBLIC ${LCMS2_INCLUDE_DIRS})
target_compile_options(icc PUBLIC ${LCMS2_CFLAGS_OTHER})

#######################################
# Config
if (KWIN_BUILD_KCMS)
    set(kwin_icc_config_SRCS icc_config.cpp)

    ki18n_wrap_ui(kwin_icc_config_SRCS icc_config.ui)
    kconfig_add_kcfg_files(kwin_icc_config_SRCS iccconfig.kcfgc)
    kwin_add_effect_config(kwin_icc_config ${kwin_icc_config_SRCS})

    target_link_libraries(kwin_icc_config
        KF6::KCMUtils
        KF6::CoreAddons
        KF6::GlobalAccel
        KF6::I18n
        KF6::XmlGui
        KWinEffectsInterface
#        KF5::ConfigWidgets
#        KF5::Service
    )
endif()
