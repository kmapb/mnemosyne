project('tutorial', 'cpp', default_options: ['cpp_std=c++20'])

ssl_dep = dependency('openssl', required: true)

mnem_sources = [ 'value.cpp' ]
mnem_lib = library('mnem', mnem_sources,
  dependencies: [ssl_dep],
  include_directories: include_directories('.'))
mnem_dep = declare_dependency(link_with: mnem_lib, include_directories: include_directories('.'))

postgres_dep = dependency('libpq', required: true)
pqxx_dep = dependency('libpqxx', required: true)
gtest_dep = dependency('gtest', required: true)

executable('demo', 'main.cpp',
  dependencies: [ postgres_dep, pqxx_dep, mnem_dep ],
  install: true)

executable('test_value', 'test/test_value.cpp',
  dependencies: [ postgres_dep, pqxx_dep, mnem_dep, gtest_dep],
  install: false)