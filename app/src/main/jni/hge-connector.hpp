#ifndef HGECLIENTCONNECTOR_HPP
#define HGECLIENTCONNECTOR_HPP
namespace hge
{
	namespace core
	{
		class ApplicationUnit;
	}
	namespace utility
	{
		class Connector
		{
		public:
			typedef enum
			{
				channel_already_exist
			} errors;
			/// This function run the Channel.
			virtual void startConnection() = 0;
			virtual void terminateConnection() = 0;
			virtual void setApplication(core::ApplicationUnit *const &application) = 0;
			virtual core::ApplicationUnit *getApplication() = 0;
			virtual void sendData(const unsigned int &size, const unsigned char *const &data) = 0;
		};
	}
}
#endif
