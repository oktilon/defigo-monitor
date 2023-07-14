project(
    'monitor', 'c',
    version : '1.0.0',
    meson_version : '> 0.53.0')

# Global parameters
version_arr = meson.project_version().split('.')
monitor_path_prefix = '/com/getdefigo'
monitor_name_prefix = 'com.getdefigo.'

# Set configuration data
conf_data = configuration_data()
conf_data.set('version_major', version_arr[0])
conf_data.set('version_minor', version_arr[1])
conf_data.set('version_rev',   version_arr[2])
conf_data.set('monitor_path_prefix', monitor_path_prefix)
conf_data.set('monitor_name_prefix', monitor_name_prefix)

# Includes
inc = include_directories('include')

# Sources
src = [
      'src/bus.c'
    , 'src/app.c'
]

# Dependencies
deps = [
      dependency('libsystemd')
]

# Create config file
configure_file(
    input : 'app.h.in',
    output : 'app.h',
    configuration : conf_data
)

# Create executable
executable(
    meson.project_name(),
    sources : src,
    include_directories : inc,
    dependencies : deps
)
