/*
 * unbind.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_UNBIND_H_
#define SMPP_PDU_UNBIND_H_

#include "pdu.h"

#pragma pack(push, 1)

namespace smpp {
	namespace pdu {

		class unbind: public pdu {
		public:
			unbind(uint32_t sequence_number):
				pdu(UNBIND) {
				this->sequence_number = sequence_number;
			}
		};

		class unbind_resp: public pdu {
		public:
			unbind_resp(uint32_t sequence_number):
				pdu(UNBIND_RESP) {
				this->sequence_number = sequence_number;
			}
		};


	};
};

#pragma pack(pop)
#endif /* SMPP_PDU_UNBIND_H_ */
