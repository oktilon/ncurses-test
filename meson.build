project('forms', 'cpp', version:'0.1.0')

# Includes and sources
# inc = include_directories('include')
src = [
      'src/app.cpp'
]

# Dependencies
deps = [
      dependency('ncurses')
]

# Create executable
executable(
      meson.project_name(),
      sources : src,
      # include_directories : inc,
      dependencies : deps,
      # link_args: ['-lpanel', '-lform']
)
