# CMake generated Testfile for 
# Source directory: D:/dev/work/sandbox/test/3rdParty/libpqxx/test/unit
# Build directory: D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/test/unit
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(unit_runner "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/test/unit/Debug/unit_runner.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(unit_runner "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/test/unit/Release/unit_runner.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(unit_runner "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/test/unit/MinSizeRel/unit_runner.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(unit_runner "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/test/unit/RelWithDebInfo/unit_runner.exe")
else()
  add_test(unit_runner NOT_AVAILABLE)
endif()
