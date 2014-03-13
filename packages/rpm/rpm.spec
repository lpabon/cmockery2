%global _for_fedora_koji_builds 0
Name:           cmockery2
Summary:        Lightweight C unit testing framework.
Version:        1.3.3
Release:        1%{?dist}
Group:          Development/Tools
URL:            https://github.com/lpabon/%{name}
License:        ASL 2.0
%if ( 0%{_for_fedora_koji_builds} )
Source0:        https://github.com/lpabon/%{name}/archive/%{version}.tar.gz
%else
Source0:        %{name}-%{version}.tar.gz
%endif
Buildroot:      %{_tmppath}/%{name}-root
BuildRequires:    gcc make automake libtool

%description
Cmockery tests are compiled into stand-alone executables and linked
with the Cmockery library, the standard C library and module being
tested. Any symbols external to the module being tested should be
mocked - replaced with functions that return values determined by
the test - within the test application. Even though significant
differences may exist between the target execution environment of a
code module and the environment used to test the code the unit
testing is still valid since its goal is to test the logic of a
code modules at a functional level and not necessarily all of its
interactions with the target execution environment.

Other features:
* Lightweight C Unit test with mocking support
* JUnit XML report output which can be used with Jenkins
* Provides design-by-contract support

This project is a successor of http://code.google.com/p/cmockery-staging/
which is a successor of Google's http://code.google.com/p/cmockery/.

%package devel
Summary:        Lightweight C unit testing framework.
Group:          Development/Tools
Requires:       %{name} = %{version}-%{release}

%description devel
Cmockery tests are compiled into stand-alone executables and linked
with the Cmockery library, the standard C library and module being
tested. Any symbols external to the module being tested should be
mocked - replaced with functions that return values determined by
the test - within the test application. Even though significant
differences may exist between the target execution environment of a
code module and the environment used to test the code the unit
testing is still valid since its goal is to test the logic of a
code modules at a functional level and not necessarily all of its
interactions with the target execution environment.

Other features:
* Lightweight C Unit test with mocking support
* JUnit XML report output which can be used with Jenkins
* Provides design-by-contract support

This project is a successor of http://code.google.com/p/cmockery-staging/
which is a successor of Google's http://code.google.com/p/cmockery/.

Package provides necessary headers for C unit test development

%package static
Summary:        Lightweight C unit testing framework.
Group:          Development/Tools
Requires:       %{name}-devel = %{version}-%{release}

%description static
Cmockery tests are compiled into stand-alone executables and linked
with the Cmockery library, the standard C library and module being
tested. Any symbols external to the module being tested should be
mocked - replaced with functions that return values determined by
the test - within the test application. Even though significant
differences may exist between the target execution environment of a
code module and the environment used to test the code the unit
testing is still valid since its goal is to test the logic of a
code modules at a functional level and not necessarily all of its
interactions with the target execution environment.

Other features:
* Lightweight C Unit test with mocking support
* JUnit XML report output which can be used with Jenkins
* Provides design-by-contract support

This project is a successor of http://code.google.com/p/cmockery-staging/
which is a successor of Google's http://code.google.com/p/cmockery/.

This package provides a static C library

%prep
%setup -q

%build
./autogen.sh
%configure
make

%check
make check

%install
rm -rf %{buildroot}
%make_install

%clean
rm -rf %{buildroot}

%files
%doc AUTHORS README README.md ChangeLog COPYING
%{_libdir}/libcmockery.so*

%files devel
%{_includedir}/cmockery*
%{_prefix}/share/doc/cmockery*
%{_libdir}/libcmockery.la

%files static
%{_libdir}/libcmockery.a

%changelog
* Thu Mar 13 2014 Luis Pabon, Jr. <lpabon@redhat.com>
- Version v1.3.3
- Initial Fedora release

