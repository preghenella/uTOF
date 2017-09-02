set(MODULE dataFormat)

set(SOURCES
    Hit.cxx
    Channel.cxx
    Writer.cxx
    StripWriter.cxx
    )

set(HEADERS
    Hit.h
    Channel.h
    Writer.h
    StripWriter.h
    )

uTOF_GENERATE_LIBRARY()
