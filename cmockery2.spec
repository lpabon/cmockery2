Name:           cmockery2
Summary:        Lightweight C unit testing framework
Version:        1.3.9
Release:        1%{?dist}
Group:          System Environment/Libraries
URL:            https://github.com/lpabon/%{name}
License:        ASL 2.0
Source0:        https://github.com/lpabon/%{name}/archive/v%{version}/%{name}-%{version}.tar.gz
Buildroot:      %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)
BuildRequires:    automake libtool pkgconfig

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
Group:          Development/Libraries
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

%prep
%setup -q

%build
./autogen.sh
%configure
make %{?_smp_mflags}

%install
%{__rm} -rf %{buildroot}
%if ( 0%{?rhel} && 0%{?rhel} < 6 )
#EL5 does not have the make_install macro
make install DESTDIR=%{buildroot}
%else
%make_install
%endif

%check
make check

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
%{_libdir}/pkgconfig/cmockery2.pc
%exclude %{_libdir}/libcmockery.a
%exclude %{_libdir}/libcmockery.la

%changelog
* Mon Apr 13 2015 Luis Pabón, Jr. <lpabon@redhat.com> - 1.3.9-1
- Minor bug fixes

* Tue Jun 17 2014 Luis Pabón, Jr. <lpabon@redhat.com> - 1.3.8-1
- clang support

* Mon Mar 24 2014 Luis Pabon, Jr. <lpabon@redhat.com> - 1.3.7-1
- Fixed memory check functions
- Added new memory unit test

* Fri Mar 21 2014 Luis Pabon, Jr. <lpabon@redhat.com> - 1.3.6-1
- PPC fixes

* Thu Mar 13 2014 Luis Pabon, Jr. <lpabon@redhat.com> - 1.3.4-1
- Initial Fedora release

