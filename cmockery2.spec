%global _for_fedora_koji_builds 0
Name:           cmockery2
Summary:        Lightweight C unit testing framework
Version:        1.3.4
Release:        1%{?dist}
Group:          Development/Tools
URL:            https://github.com/lpabon/%{name}
License:        ASL 2.0
%if ( 0%{_for_fedora_koji_builds} )
Source0:        https://github.com/lpabon/%{name}/archive/v%{version}/%{name}-%{version}.tar.gz
%else
Source0:        %{name}-%{version}.tar.gz
%endif
Buildroot:      %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)
BuildRequires:    automake libtool

%description
Cmockery tests are compiled into a stand-alone executable and linked
with the cmockery library, the standard C library and module being
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
Summary:        Lightweight C unit testing framework
Group:          Development/Tools
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description devel
Cmockery tests are compiled into a stand-alone executable and linked
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
Summary:        Lightweight C unit testing framework
Group:          Development/Tools
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description static
Cmockery tests are compiled into a stand-alone executable and linked
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
%{__rm} -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%clean
%{__rm} -rf %{buildroot}

%files
%{_docdir}/cmockery*
%{_libdir}/libcmockery.so.*

%files devel
%{_includedir}/cmockery*
%{_libdir}/libcmockery.so

%files static
%{_libdir}/libcmockery.a
%exclude %{_libdir}/libcmockery.la

%changelog
* Thu Mar 13 2014 Luis Pabon, Jr. <lpabon@redhat.com> - 1.3.4-1
- Initial Fedora release

