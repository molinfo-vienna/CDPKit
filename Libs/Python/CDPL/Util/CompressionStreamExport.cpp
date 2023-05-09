/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CompressionStreamExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <boost/python.hpp>

#include "CDPL/Util/CompressionStreams.hpp"

#include "Base/IOStream.hpp"

#include "ClassExports.hpp"


namespace
{

	template <typename Impl>
    class CompressedIStream : public CDPLPythonBase::IOStream<Impl>, 
							  public boost::python::wrapper<CDPLPythonBase::IOStream<Impl> >
    {

    public:
		CompressedIStream(): 
			Impl(), CDPLPythonBase::IOStream<Impl>("", std::ios_base::in) {}

		CompressedIStream(std::istream& is): 
			Impl(is), CDPLPythonBase::IOStream<Impl>("", std::ios_base::in) {

			if (this->good())
				return;

			throw CDPL::Base::IOError("CompressedIStream: construction failed");
		}

		void open(std::istream& is) {
			Impl::open(is);

			if (!this->good())
				throw CDPL::Base::IOError("CompressedIStream: open failed");
		}

		void close() {
			Impl::close();

			if (!this->good())
				throw CDPL::Base::IOError("CompressedIStream: close failed");

			this->closeStream();
		}
	};

	template <typename Impl>
    class CompressedOStream : public CDPLPythonBase::IOStream<Impl>, 
							   public boost::python::wrapper<CDPLPythonBase::IOStream<Impl> >
    {

    public:
		CompressedOStream(): 
			Impl(), CDPLPythonBase::IOStream<Impl>("", std::ios_base::out) {}

		CompressedOStream(std::ostream& os): 
			Impl(os), CDPLPythonBase::IOStream<Impl>("", std::ios_base::out) {

			if (this->good())
				return;

			throw CDPL::Base::IOError("CompressedOStream: construction failed");
		}

		void open(std::ostream& os) {
			Impl::open(os);

			if (!this->good())
				throw CDPL::Base::IOError("CompressedOStream: open failed");
		}

		void close() {
			Impl::close();

			if (!this->good())
				throw CDPL::Base::IOError("CompressedOStream: close failed");

			this->closeStream();
		}
	};

	template <typename Impl>
    class CompressedIOStream : public CDPLPythonBase::IOStream<Impl>, 
							   public boost::python::wrapper<CDPLPythonBase::IOStream<Impl> >
    {

    public:
		CompressedIOStream(): 
			Impl(), CDPLPythonBase::IOStream<Impl>("", std::ios_base::in | std::ios_base::out) {}

		CompressedIOStream(std::iostream& ios): 
			Impl(ios), CDPLPythonBase::IOStream<Impl>("", std::ios_base::in | std::ios_base::out) {

			if (this->good())
				return;

			throw CDPL::Base::IOError("CompressedIOStream: construction failed");
		}

		void open(std::iostream& ios) {
			Impl::open(ios);

			if (!this->good())
				throw CDPL::Base::IOError("CompressedIOStream: open failed");
		}

		void close() {
			Impl::close();

			if (!this->good())
				throw CDPL::Base::IOError("CompressedIOStream: close failed");

			this->closeStream();
		}
	};

	template <typename Impl>
	void exportCompressionIOStream(const char* name)
	{
		using namespace boost;

		python::class_<CompressedIOStream<Impl>, python::bases<std::iostream>, boost::noncopyable>(name, python::no_init)
			.def(python::init<>(python::arg("self")))
			.def(python::init<std::iostream&>((python::arg("self"), python::arg("ios")))
				 [python::with_custodian_and_ward<1, 2>()])
			.def(CDPLPythonBase::IStreamVisitor<CompressedIOStream<Impl> >())
			.def(CDPLPythonBase::OStreamVisitor<CompressedIOStream<Impl> >())
			.def("close", &CompressedIOStream<Impl>::close, python::arg("self"))
			.def("open", &CompressedIOStream<Impl>::open, (python::arg("self"), python::arg("ios")),
				 python::with_custodian_and_ward<1, 2>());
	}

	template <typename Impl>
	void exportCompressionIStream(const char* name)
	{
		using namespace boost;

		python::class_<CompressedIStream<Impl>, python::bases<std::istream>, boost::noncopyable>(name, python::no_init)
			.def(python::init<>(python::arg("self")))
			.def(python::init<std::istream&>((python::arg("self"), python::arg("is")))
				 [python::with_custodian_and_ward<1, 2>()])
			.def(CDPLPythonBase::IStreamVisitor<CompressedIStream<Impl> >())
			.def("close", &CompressedIStream<Impl>::close, python::arg("self"))
			.def("open", &CompressedIStream<Impl>::open, (python::arg("self"), python::arg("is")),
				 python::with_custodian_and_ward<1, 2>());
	}

	template <typename Impl>
	void exportCompressionOStream(const char* name)
	{
		using namespace boost;

		python::class_<CompressedOStream<Impl>, python::bases<std::ostream>, boost::noncopyable>(name, python::no_init)
			.def(python::init<>(python::arg("self")))
			.def(python::init<std::ostream&>((python::arg("self"), python::arg("os")))
				 [python::with_custodian_and_ward<1, 2>()])
			.def(CDPLPythonBase::OStreamVisitor<CompressedOStream<Impl> >())
			.def("close", &CompressedOStream<Impl>::close, python::arg("self"))
			.def("open", &CompressedOStream<Impl>::open, (python::arg("self"), python::arg("os")),
				 python::with_custodian_and_ward<1, 2>());
	}
}


void CDPLPythonUtil::exportCompressionStreams()
{
    using namespace CDPL;

	exportCompressionIOStream<Util::GZipIOStream>("GZipIOStream");
	exportCompressionIOStream<Util::BZip2IOStream>("BZip2IOStream");

	exportCompressionIStream<Util::GZipIStream>("GZipIStream");
	exportCompressionIStream<Util::BZip2IStream>("BZip2IStream");

	exportCompressionOStream<Util::GZipOStream>("GZipOStream");
	exportCompressionOStream<Util::BZip2OStream>("BZip2OStream");
}
