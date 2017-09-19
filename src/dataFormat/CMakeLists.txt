set(MODULE dataFormat)

set(SOURCES
    Hit.cxx
    Channel.cxx
    Writer.cxx
    StripWriter.cxx
    )

set(HEADERS
    dataFormat/Hit.h
    dataFormat/Channel.h
    dataFormat/Writer.h
    dataFormat/StripWriter.h
    )

uTOF_GENERATE_LIBRARY()
