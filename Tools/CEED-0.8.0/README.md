# CEGUI Unified Editor

## User Manual
CEED comes with a beautifully formatted PDF explaining many of its functions. *Please, read it!* Seriously, **please read the manual**. It comes as a PDF in the release tarballs, you can also build it yourself if you have LyX - see the *doc* folder.

Alternatively visit http://static.cegui.org.uk/docs/ and select the appropriate CEED version.

## Other Resources
- [Community page for CEED](http://www.cegui.org.uk/wiki/index.php/CEED) - and don't hesitate to improve that page!
- [Step-by-step guide for building CEED on Windows](http://cegui.org.uk/wiki/Building_CEED_for_Windows) - Again, don't hesitate to improve wiki pages!
- Join the `#cegui` channel on `irc.freenode.net`
- The **developer manual** - comes in tarballs, or you can build it yourself, alternatively visit http://static.cegui.org.uk/docs/

## Contributing

We are happiest with **clean pull requests** containing conscise commits with **proper commit messages**. We also accept **plain patches** but making it easier for us to just accept your contribution with one click greatly speeds up the review process.

- Join the `#cegui` and `#cegui-devel` channels on `irc.freenode.net`

## Quick Start Guide

### Dependencies
1. Python 2.7+ (but not Python 3)
   > If you have *32bit* CEGUI you have to use *32bit* Python, the arch has to match!
   > It is recommended to use the same toolchain to build PyCEGUI that your Python was built with, on Windows with Python 2.7 this will most likely be *MSVC 2008*.
2. CEGUI 0.8.x with PyCEGUI
3. Qt 4.7+ with PySide
4. PyOpenGL

### Requirements
You need an OpenGL capable GPU with **FBO** support. CEED will run without that but layout editing will exhibit artifacts.

CEED was tested on Linux, MacOS X, Windows and FreeBSD. It may or may not run on other systems.

### Starting CEED

#### system-wide install (Linux or MacOS X)
```bash
# as root
python setup.py install
```

Then you can start CEED using
```bash
ceed-gui
```

You can also use the other tools called `ceed-migrate` and `ceed-mic`.

#### local developer setup (without installation) on Linux, BSD, OS X, etc...

Go to "bin" and start runwrapper.sh. It will spawn a shell with PYTHONPATH defined so that "ceed" is found properly.

```bash
cd ceed/bin
# runwrapper creates the necessary environment
./runwrapper.sh
# start CEED
./ceed-gui
# you can also use debugging tools - pdb, gdb, cgdb, valgrind - in the environment
```

See the script's contents for more details.

#### local developer setup (without installation) on Windows

The only difference is that you need to start `runwrapper.bat` and the script will start ceed-gui automatically. This is the preferred choice on Windows because the terminal emulators are horrible.

## Troubleshooting

### Can't import ceed.ui.something

You haven't got the .ui files compiled. Compile them with `./maintenance compile-ui-files` or switch to developer mode (see ceed/version.py)

Released CEED versions come with compiled UI files but these are not committed to the repository. Either use a released tarball or compile UI files as instructed above.

If you are developing CEED you probably don't want to manually compile UI files all the time, switch to the developer mode in ceed/version.py and it will be done automatically every time CEED starts.

### Module ceed not found
Unless you have installed ceed system-wide, you have to set several environment variables so that everything is found correctly.

Please see the section `Starting CEED` above.


## CEED vs CEGUI Editor vs CEGUI Unified Editor

Yes, there is some confusion regarding the names. CEGUI has had many editors in the past and we sort of ran out of ideas. CEED stands for `CE`gui`ED`itor. It's very often also called "CEGUI Unified Editor" because it has features previously only available in multiple editor applications.
