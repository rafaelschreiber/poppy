# uncomment as necessary
project('pop3client_29', 'cpp',
        license : ['Boost'],
        version : '0.3',
        default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=false'])

# thread_dep = dependency('threads')
gnutls_dep = dependency('gnutls')

# CLI11: https://github.com/CLIUtils/CLI11
add_global_arguments('-I' + get_option('cli11_include_dir'), language : 'cpp')

# spdlog: https://github.com/gabime/spdlog
add_global_arguments('-I' + get_option('spdlog_include_dir'), language : 'cpp')

# json: https://github.com/nlohmann/json
add_global_arguments('-I' + get_option('json_include_dir'), language : 'cpp')

# tabulate: https://github.com/p-ranav/tabulate
add_global_arguments('-I' + get_option('tabulate_include_dir'), language : 'cpp')

# tfile: https://github.com/rec/tfile
add_global_arguments('-I' + get_option('tfile_include_dir'), language : 'cpp')

inc_dir = include_directories('include')
src = ['src/main.cpp', 'src/mailbox.cpp', 'src/pop3socket.cpp', 'src/pystring.cpp']

executable('pop3client',
           sources : src,
           include_directories : inc_dir,
           dependencies : [gnutls_dep]
)
