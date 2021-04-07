# uncomment as necessary
project('pop3client_29', 'cpp',
        license : ['Boost'],
        version : '0.4',
        default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=false', ])

# thread_dep = dependency('threads')
gnutls_dep = dependency('gnutls')
mailutils_dep = declare_dependency(link_args : ['-L/usr/local/lib', '-lmailutils'], include_directories : ['/usr/local/include'])
protobuf_dep = dependency('protobuf')
grpc_dep = declare_dependency(link_args : ['-L/usr/local/lib', '-lgrpc++'])

# Disable some warnings for a cleaner compilation
add_global_arguments(['-Wno-unused-parameter', '-Wno-non-virtual-dtor'], language : 'cpp')

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

# compile protobuf definition and move generated protobuf and grpc files
run_command('protos/compile_protobuf_grpc.sh')

inc_dir = include_directories('include')
src = ['src/main.cpp', 'src/mailbox.cpp', 'src/pop3socket.cpp', 
       'src/pystring.cpp', 'src/pop3client.pb.cc', 'src/pop3client.grpc.pb.cc']

executable('pop3client',
           sources : src,
           include_directories : inc_dir,
           dependencies : [gnutls_dep, mailutils_dep, protobuf_dep, grpc_dep]
)
