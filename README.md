# CoverArtArchive Client Library


Documentation
-------------

To get started quickly have a look at the examples directory which
contains various sample programs. API documentation can be generated
using [Doxygen](https://github.com/doxygen/doxygen). The online version of
the API documentation can be found [here](https://metabrainz.github.io/libcoverart/1.0.0/).

Compiling and Linking
---------------------

This package provides a pkg-config script that returns the necessary compiler
and linker flags, as well as the version number.  To build a small sample
program using the C++ API one would use:

    g++ -o test_app test_app.cpp `pkg-config libcoverartcc --cflags --libs`

To build a small sample program using the C API one would use:

    gcc -o test_app test_app.c `pkgconfig libcoverart --cflags --libs`

If you don't want/can't use pkg-config and you are using the C API, make sure
you link in the C++ standard library:

    gcc -o test_app test_app.c -lcoverart -lm -lstdc++

Contact
-------

If you have any questions about this library, feel free to ask on the
MusicBrainz development mailing list:

    http://lists.musicbrainz.org/mailman/listinfo/musicbrainz-devel

Please submit bug reports to the MusicBrainz bug tracking system:

    http://tickets.musicbrainz.org/browse/LCA

You can find out more about the MusicBrainz project by visiting its
site:

    http://musicbrainz.org/
