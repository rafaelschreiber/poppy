project('POPpy', 'cpp',
        license : ['Boost'],
        version : '1.0',
        default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=false'])

# check program dependencies
assert(run_command('which', 'protoc').returncode() == 0, 'protoc is missing but required (https://grpc.io/docs/protoc-installation)')
assert(run_command('which', 'grpc_cpp_plugin').returncode() == 0, 'grpc_cpp_plugin is missing but required (https://grpc.io/docs/languages/cpp/quickstart)')
assert(run_command('which', 'protoc-gen-grpc-web').returncode() == 0, 'protoc-gen-grpc-web is missing but required (https://github.com/grpc/grpc-web/releases)')
assert(run_command('which', 'envoy').returncode() == 0, 'envoy is missing but required (https://www.envoyproxy.io)')
assert(run_command('which', 'npm').returncode() == 0, 'npm is missing but required (https://www.npmjs.com/get-npm)')

# declare dependencies; change them to your library path
thread_dep = dependency('threads')
gnutls_dep = dependency('gnutls')
protobuf_dep = dependency('protobuf')
mailutils_dep = declare_dependency(link_args : ['-lmailutils'])

if host_machine.system() == 'darwin' # pkg-config for grpc++ on macOS is broken
  grpc_dep = declare_dependency(link_args : ['-lgrpc++'])
else
  grpc_dep = dependency('grpc++')
endif

# Disable some warnings for a cleaner compilation
add_global_arguments(['-Wno-unused-parameter', '-Wno-non-virtual-dtor'], language : 'cpp')

# CLI11: https://github.com/CLIUtils/CLI11
add_global_arguments('-I' + get_option('cli11_include_dir'), language : 'cpp')

# spdlog: https://github.com/gabime/spdlog
add_global_arguments('-I' + get_option('spdlog_include_dir'), language : 'cpp')

# subprocess: https://github.com/arun11299/cpp-subprocess
add_global_arguments('-I' + get_option('subprocess_include_dir'), language : 'cpp')

# toml++: https://github.com/marzer/tomlplusplus
add_global_arguments('-I' + get_option('toml_include_dir'), language : 'cpp')

# add prefix preprocessor define
add_global_arguments('-D__PREFIX__="' + get_option('prefix') + '"', language : 'cpp')

# compile protobuf definition and move generated protobuf and gRPC files
if run_command('test', '-f', 'src/poppy.grpc.pb.cc').returncode() != 0
  message('Compiling protobuf & grpc files...')
  protobuf_compile = run_command('protos/compile_protobuf_grpc.sh')
  if protobuf_compile.returncode() != 0
    message(protobuf_compile.stderr().strip())
    error('Failed compile protobuf and gRPC files from proto/poppy.proto')
  endif 
  message('Protobuf & gRPC files successfully compiled!')
endif

# compile javascript frontend
if run_command('test', '-f', 'share/poppy/js/dist/main.js').returncode() != 0
  message('Compiling javascript frontend files...')
  frontend_compile = run_command('share/poppy/js/compile_javascript_frontend.sh')
  if frontend_compile.returncode() != 0
    message(frontend_compile.stderr().strip())
    error('Failed compile javascript frontend in share/poppy/js/')
  endif
  message('Javascript frontend files successfully compiled!')
endif

inc_dir = include_directories('include')
src = ['src/main.cpp', 'src/mailbox.cpp', 'src/pop3socket.cpp', 
       'src/pystring.cpp', 'src/poppy.pb.cc', 'src/poppy.grpc.pb.cc',
       'src/mailservice.cpp', 'src/globals.cpp']

meson.add_install_script('install.sh')

executable('poppy',
           sources : src,
           include_directories : inc_dir,
           dependencies : [thread_dep, gnutls_dep, mailutils_dep, protobuf_dep, grpc_dep],
)
