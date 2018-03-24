#include <fstream>
#include <iostream>
#include <string>


/* Goal: Have the server configured so that whenever a login is requested,
 * this is called, looking through its log, it will either confirm or deny
 * the request.
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
				int FOBCode[4];
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
			
		public:
			Check();
			void readUsers();
			void readLog();
			void recordCurrentAttempt();
			bool determineWhetherToLock(); // will be called by main() separately
			void suspendManually();
			void restore();
			int explainError();
	};
}
