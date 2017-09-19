set(MODULE calibration)

set(SOURCES
    Base.cxx
    Offset.cxx
    Slewing.cxx
    Walk.cxx
    Channel.cxx
    )

set(HEADERS
    calibration/Base.h
    calibration/Offset.h
    calibration/Slewing.h
    calibration/Walk.h
    calibration/Channel.h
    )

set(MODULE_DEPENDENCIES uTOFdataFormat)

uTOF_GENERATE_LIBRARY()
