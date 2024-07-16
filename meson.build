project('tutorial', 'cpp', default_options: ['cpp_std=c++20'])

postgres_dep = dependency('libpq', required: true)

executable('demo', 'main.cpp',
  dependencies: [postgres_dep],
  install: true)
