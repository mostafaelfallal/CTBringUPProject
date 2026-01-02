# Define the root build directory relative to this file
# $$PWD is the directory containing defaults.pri
BUILD_ROOT = $$PWD/build

# 1. Put the executable (Client/Server) in a common "bin" folder
DESTDIR = $$BUILD_ROOT/bin

# 2. Put intermediate object files (*.o) in organized subfolders
OBJECTS_DIR = $$BUILD_ROOT/$$TARGET/obj

# 3. Put Meta-Object Compiler files (moc_*.cpp) in organized subfolders
MOC_DIR = $$BUILD_ROOT/$$TARGET/moc

# 4. Put Resource files (optional) in organized subfolders
RCC_DIR = $$BUILD_ROOT/$$TARGET/rcc