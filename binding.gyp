{
    "targets": [
        {
            "target_name": "node-source-highlight",
            "sources": ["native/SourceHighlight.cc"],
            "dependencies": [],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include_dir\")"
            ],
            "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
            'cflags!': [ '-fno-exceptions' ],
            'cflags_cc!': [ '-fno-exceptions', '-fno-rtti' ],
            "cflags_cc": ["-frtti"],
            "link_settings": {
                "libraries": [
                    "-lsource-highlight"
                ],
              },
            "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                "CLANG_CXX_LIBRARY": "libc++",
                "MACOSX_DEPLOYMENT_TARGET": "10.7"
            },
            'conditions': [
                ['OS=="mac"', {
                    'cflags+': ['-fvisibility=hidden'],
                    'xcode_settings': {
                        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                        "GCC_ENABLE_CPP_RTTI": "YES",
                        "CLANG_CXX_LIBRARY": "libc++",
                        "MACOSX_DEPLOYMENT_TARGET": "10.7",
                        'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES' # -fvisibility=hidden
                    }
                }]
            ]
        }
    ]
}