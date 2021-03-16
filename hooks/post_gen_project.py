"""Post-project generation hooks"""

if __name__ == '__main__':
    """Initialize as a git repository and add Catch2"""

    import subprocess

    # As git
    subprocess.call(('git', 'init'))

    # Get Catch2
    subprocess.call(('git', 'submodule', 'add', '-b', 'v2.x', 'https://github.com/catchorg/Catch2.git', './Tests/vendors/Catch2'))
