#ifndef DA_NOTIFY_H
#define DA_NOTIFY_H

#include "stdafx.h"

namespace dacore {

	class Notify {
	public:

		virtual ~Notify(){
			m_sig.disconnect_all_slots();
		}

		typedef boost::signals2::signal<void(const std::string&)>  signal_t;

		static boost::signals2::connection connect(const signal_t::slot_type &subscriber){
			return m_sig.connect(subscriber);
		}

		static void notify(const std::string& pname){
			m_sig(pname);
		}

	private:
		static signal_t m_sig;
	};

}

#endif