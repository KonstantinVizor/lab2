from distutils.sysconfig import get_python_inc
import platform
import os.path as p
import subprocess
DIR_OF_THIS_SCRIPT = p.abspath( p.dirname( __file__ ) )
DIR_OF_THIRD_PARTY = p.join( DIR_OF_THIS_SCRIPT, 'third_party' )
DIR_OF_WATCHDOG_DEPS = p.join( DIR_OF_THIRD_PARTY, 'watchdog_deps' )
SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]
database = None
flags = [
'-Wall',
'-Wextra',
'-Werror',
'-Wno-long-long',
'-Wno-variadic-macros',
'-fexceptions',
'-DNDEBUG',
'-DUSE_CLANG_COMPLETER',
'-DYCM_EXPORT=',
'-DYCM_ABSEIL_SUPPORTED',
'-x',
'c++',
'-isystem',
'cpp/absl',
'-isystem',
'cpp/pybind11',
'-isystem',
'cpp/whereami',
'-isystem',
'cpp/BoostParts',
'-isystem',
get_python_inc(),
'-isystem',
'cpp/llvm/include',
'-isystem',
'cpp/llvm/tools/clang/include',
'-I',
'cpp/ycm',
'-I',
'cpp/ycm/ClangCompleter',
'-isystem',
'cpp/ycm/tests/gmock/googlemock/include',
'-isystem',
'cpp/ycm/tests/gmock/googletest/include',
'-isystem',
'cpp/ycm/benchmarks/benchmark/include',
'-std=c++17',
'-I/usr/include/qt',
'-I/usr/include/opencv4'
'-I/usr/include/qt6/QtWidgets',
'-I/usr/include/qt6',
'-DQT_WIDGETS_LIB',
'-I/usr/lib/qt6/mkspecs/linux-g++',
'-I/usr/include/qt6/QtCore',
'-DQT_CORE_LIB',
'-I/usr/include/qt6/QtGui',
'-DQT_GUI_LIB',
'-I./code/libPoco/'
]
compilation_database_folder = ''
def IsHeaderFile( filename ):
  extension = p.splitext( filename )[ 1 ]
  return extension in [ '.h', '.hxx', '.hpp', '.hh' ]
def FindCorrespondingSourceFile( filename ):
  if IsHeaderFile( filename ):
    basename = p.splitext( filename )[ 0 ]
    for extension in SOURCE_EXTENSIONS:
      replacement_file = basename + extension
      if p.exists( replacement_file ):
        return replacement_file
  return filename
def PathToPythonUsedDuringBuild():
  try:
    filepath = p.join( DIR_OF_THIS_SCRIPT, 'PYTHON_USED_DURING_BUILDING' )
    with open( filepath ) as f:
      return f.read().strip()
  except OSError:
    return None
def Settings( **kwargs ):
  
  import ycm_core
  global database
  if database is None and p.exists( compilation_database_folder ):
    database = ycm_core.CompilationDatabase( compilation_database_folder )
  language = kwargs[ 'language' ]
  if language == 'cfamily':
    filename = FindCorrespondingSourceFile( kwargs[ 'filename' ] )
    if not database:
      return {
        'flags': flags,
        'include_paths_relative_to_dir': DIR_OF_THIS_SCRIPT,
        'override_filename': filename
      }
    compilation_info = database.GetCompilationInfoForFile( filename )
    if not compilation_info.compiler_flags_:
      return {}
    final_flags = list( compilation_info.compiler_flags_ )
    try:
      final_flags.remove( '-stdlib=libc++' )
    except ValueError:
      pass
    return {
      'flags': final_flags,
      'include_paths_relative_to_dir': compilation_info.compiler_working_dir_,
      'override_filename': filename
    }
  if language == 'python':
    return {
      'interpreter_path': PathToPythonUsedDuringBuild(),
      'ls': {
        'python': {
          'analysis': {
            'extraPaths': [
              p.join( DIR_OF_THIS_SCRIPT ),
              p.join( DIR_OF_THIRD_PARTY, 'bottle' ),
              p.join( DIR_OF_THIRD_PARTY, 'regex-build' ),
              p.join( DIR_OF_THIRD_PARTY, 'frozendict' ),
              p.join( DIR_OF_THIRD_PARTY, 'jedi_deps', 'jedi' ),
              p.join( DIR_OF_THIRD_PARTY, 'jedi_deps', 'parso' ),
              p.join( DIR_OF_WATCHDOG_DEPS, 'watchdog', 'build', 'lib3' ),
              p.join( DIR_OF_WATCHDOG_DEPS, 'pathtools' ),
              p.join( DIR_OF_THIRD_PARTY, 'waitress' )
            ],
            'useLibraryCodeForTypes': True
          }
        }
      }
    }
  return {}
def PythonSysPath( **kwargs ):
  sys_path = kwargs[ 'sys_path' ]
  sys_path[ 0:0 ] = [ p.join( DIR_OF_THIS_SCRIPT ),
                      p.join( DIR_OF_THIRD_PARTY, 'bottle' ),
                      p.join( DIR_OF_THIRD_PARTY, 'regex-build' ),
                      p.join( DIR_OF_THIRD_PARTY, 'frozendict' ),
                      p.join( DIR_OF_THIRD_PARTY, 'jedi_deps', 'jedi' ),
                      p.join( DIR_OF_THIRD_PARTY, 'jedi_deps', 'parso' ),
                      p.join( DIR_OF_WATCHDOG_DEPS,
                              'watchdog',
                              'build',
                              'lib3' ),
                      p.join( DIR_OF_WATCHDOG_DEPS, 'pathtools' ),
                      p.join( DIR_OF_THIRD_PARTY, 'waitress' ) ]
  sys_path.append( p.join( DIR_OF_THIRD_PARTY, 'jedi_deps', 'numpydoc' ) )
  return sys_path
