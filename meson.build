project('tutorial', 'cpp', default_options: ['cpp_std=c++20'])

postgres_dep = dependency('libpq', required: true)
pqxx_dep = dependency('libpqxx', required: true)
gtest_dep = dependency('gtest', required: true)

executable('demo', 'main.cpp',
  dependencies: [ postgres_dep, pqxx_dep ],
  install: true)

executable('test_value', 'test/test_value.cpp',
  dependencies: [ postgres_dep, pqxx_dep, gtest_dep],
  install: false)