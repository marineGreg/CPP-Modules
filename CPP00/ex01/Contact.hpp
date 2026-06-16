
#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

/*
  CONCEPTS C++ :

    - Encapsulation (Hiding data):
      Les informations du contact (nom, secret, etc.) sont en 'private'.
      Personne à l'extérieur ne peut les modifier directement.
      On utilise des "Setters" (pour écrire) et des "Getters" (pour lire).

    - std::string:
      Contrairement au char* du C, la std::string est un objet qui gère 
      sa propre mémoire. On peut la comparer avec '==' et connaître 
      sa taille avec '.length()'.

    - Const-correctness:
      Les fonctions 'get' sont marquées 'const' car elles ne modifient 
      pas l'objet. C'est une garantie de sécurité en C++.
*/
class Contact {
	private:
		std::string _firstName;
		std::string _lastName;
		std::string _nickName;
		std::string _phoneNumber;
		std::string _darkestSecret;

	public:
		Contact();
		~Contact();
		
		/* ------------- S E T T E R S ------------- */
        void setFirstName(const std::string str);
        void setLastName(const std::string str);
        void setNickName(const std::string str);
        void setPhoneNumber(const std::string str);
		void setDarkestSecret(const std::string str);
		
        /* ------------- G E T T E R S ------------- */
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getNickName() const;
        std::string getPhoneNumber() const;
        std::string getDarkestSecret() const;
};

#endif
