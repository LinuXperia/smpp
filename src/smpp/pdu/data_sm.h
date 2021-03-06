/*
 * data_sm.h
 *
 *  Created on: Jul 23, 2016
 *      Author: jamil
 */

#ifndef SMPP_PDU_DATA_SM_H_
#define SMPP_PDU_DATA_SM_H_

#include "../smpp/pdu/pdu.h"

namespace smpp {
	namespace pdu {

		struct data_sm: public pdu {
			char service_type[6];
	
			smpp::address::address<65> source_addr;
			smpp::address::address<65> destination_addr;

			uint8_t esm_struct;
			uint8_t registerd_delivery;
			uint8_t data_coding;

			//Message Submission TLVs

			data_sm():
				pdu(DATA_SM) {

			}

			virtual ~data_sm() {

			}
		};

		struct data_sm_resp: public pdu {
			char message_id[65];
			//Message submission Response TLVs
			data_sm_resp():
				pdu(DATA_SM_RESP) {

			}

			virtual ~data_sm_resp() {

			}
		};



	};

};
#endif /* SMPP_PDU_DATA_SM_H_ */
