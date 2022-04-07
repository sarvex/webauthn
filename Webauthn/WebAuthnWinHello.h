#pragma once

#ifdef _WIN32

#include "WebAuthnImpl.h"

#include <Windows.h>
#include <webauthn.h>

#include <memory>

namespace webauthn::impl
{
	class WebAuthnWinHello : public WebAuthnImpl
	{
	public:
		using WebAuthNGetApiVersionNumber_t = decltype(&WebAuthNGetApiVersionNumber);
		using WebAuthNIsUserVerifyingPlatformAuthenticatorAvailable_t = decltype(&WebAuthNIsUserVerifyingPlatformAuthenticatorAvailable);
		using WebAuthNAuthenticatorMakeCredential_t = decltype(&WebAuthNAuthenticatorMakeCredential);
		using WebAuthNGetErrorName_t = decltype(&WebAuthNGetErrorName);
		using WebAuthNFreeAssertion_t = decltype(&WebAuthNFreeAssertion);
		using WebAuthNFreeCredentialAttestation_t = decltype(&WebAuthNFreeCredentialAttestation);

		class WebAuthnWinHelloDll
		{
		public:
			WebAuthnWinHelloDll();
			~WebAuthnWinHelloDll();

			WebAuthNGetApiVersionNumber_t WebAuthNGetApiVersionNumber{ nullptr };
			WebAuthNIsUserVerifyingPlatformAuthenticatorAvailable_t WebAuthNIsUserVerifyingPlatformAuthenticatorAvailable{ nullptr };
			WebAuthNAuthenticatorMakeCredential_t WebAuthNAuthenticatorMakeCredential{ nullptr };
			WebAuthNGetErrorName_t WebAuthNGetErrorName{ nullptr };
			WebAuthNFreeAssertion_t WebAuthNFreeAssertion{ nullptr };
			WebAuthNFreeCredentialAttestation_t WebAuthNFreeCredentialAttestation{ nullptr };

			bool good() const noexcept { return isAvaiable; }
			operator bool() const noexcept { return isAvaiable; }

		private:
			HMODULE webauthn_lib{ nullptr };
			bool isAvaiable{};
		};

		WebAuthnWinHello();
		~WebAuthnWinHello();

		std::optional<MakeCredentialResult> makeCredential(const UserData& user, const RelyingParty& rp) override;
		std::optional<GetAssertionResult> getAssertion(const CredentialId& id, const RelyingParty& rp) override;

	private:
		WebAuthnWinHelloDll webAuthnWinHelloDll{};
	};
}

#endif // _WIN32
