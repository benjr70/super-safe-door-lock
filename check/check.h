#include <fstream>
#include <iostream>
#include <string>
#include "../sqlapi/SQLAPI.h"


/* Goal: Have the server configured so that whenever a login is requested,
 * this is called, looking through its log, it will either confirm or deny
 * the request.
 * 
 * Now, because all the timestamps will be determined BY THE CLIENT,
 * there this script just has to check the database
 * 
 * When receiving a code, it must both determine the user and 
 */

namespace CheckNS {

	class Check
	{
		private:
			enum class AuthType {STATIC_CODE, CHANGING_CODE, FOB};
			struct User
			{
				int userID;
				int changingCode;
				int staticCode;
				//make it easy to copy and paste
				char FobCODE[4];
			};
			struct Attempt
			{
				int LockID;
				int userID;
				AuthType authType;
				bool success;
				time_t time;
			};
			int * user;
			int * lock;
			bool suspendActivity;
			int errorCode;
			
			std::fstream file;
			SAConnection connection;
			SACommand command;
			
			
		
		public:
			Check();
			~Check(); // the destructor can be used to set the file
			// the file can simply indicate the number of entries
			// and if it is in an error state
			Check(int, char, int[]);
			void readData();
			void castJudgement(); // will be called by main() separately
			void suspendManually();
			void restore();
			int explainError() const;
			bool isThereAThreat() const;
	};
}
