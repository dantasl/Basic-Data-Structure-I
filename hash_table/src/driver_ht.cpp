/**
 * @file    driver_ht.cpp
 * @brief   Driver code to test functions of ac::HashTbl
 * @author  Selan Rodrigues dos Santos
 */

#include <iostream>
#include <functional>
#include <tuple>
#include <cassert>

#include "hashtbl.h"

using namespace ac;

// Tipo conta-corrente.
struct Account
{
	std::string mClientName;
	int mBankCode;
	int mBranchCode;
	int mNumber;
	float mBalance;

	// Nickname for the account key.
#if ( VERSION == 1)
        using AcctKey = int;
#elif ( VERSION == 2 )
        using AcctKey = std::pair< std::string, int >;
#else // VERSION = 3
        using AcctKey = std::tuple< std::string, int, int, int >;
#endif

        Account( std::string _n = "<empty>", // Nome
                int _bnc = 0,               // Banco do Brasil.
                int _brc = 0,               // Ag. Campus UFRN
                int _nmr = 0,               // Numero da conta
                float _bal = 0.f )          // Saldo
            : mClientName( _n )
            , mBankCode( _bnc )
            , mBranchCode( _brc )
            , mNumber( _nmr )
            , mBalance( _bal )
    { /* Empty */ }
		     
	// Retorna a chave associada com a conta-corrente.
	AcctKey getKey()
	{
#if ( VERSION == 1)
            return mNumber;
#elif ( VERSION == 2 )
            return std::pair< std::string, int >( mClientName, mNumber );
#else // VERSION = 3
            return std::make_tuple( mClientName, mBankCode, mBranchCode, mNumber );
#endif
	}
	
	// DEBUG: Imprime uma formatacao para a conta-corrente.
	inline friend std::ostream &operator<< ( std::ostream & _os, const Account & _acct )
        {

            _os << "[ Client: <" << _acct.mClientName <<
                   "> Bank: <"   << _acct.mBankCode <<
                   "> Branch: <" << _acct.mBranchCode <<
                   "> Number: <" << _acct.mNumber <<
                   "> Balance: <" << _acct.mBalance << "> ]";
            return _os;
        }
};

bool operator==( const Account & a, const Account & b )
{
    return ( a.mClientName == b.mClientName and
             a.mBankCode   == b.mBankCode and
             a.mBranchCode == b.mBranchCode and
             a.mNumber     == b.mNumber and
             a.mBalance    == b.mBalance ) ;
}

// Functor
struct KeyHash
{
    std::size_t operator()( const Account::AcctKey & _k ) const
    {
#if ( VERSION == 1)
        return std::hash< int >()( _k );
#elif ( VERSION == 2 )
        return std::hash< std::string >()( _k.first ) xor std::hash< int >()( _k.second );
#else // VERSION = 3
        return std::hash< std::string >()(std::get<0>( _k )) xor
               std::hash< int >()(std::get<1>( _k )) xor
               std::hash< int >()(std::get<2>( _k )) xor
               std::hash< int >()(std::get<3>( _k ));
#endif
    }
};


// Functor
struct KeyEqual
{
	bool operator()( const Account::AcctKey & _lhs, const Account::AcctKey & _rhs ) const
	{
#if ( VERSION == 1)
            return ( _lhs == _rhs );
#elif ( VERSION == 2 )
            return ( _lhs.first == _rhs.first and _lhs.second == _rhs.second );
#else // VERSION = 3
            return std::get<0>(_lhs) == std::get<0>(_rhs) and
                   std::get<1>(_lhs) == std::get<1>(_rhs) and
                   std::get<2>(_lhs) == std::get<2>(_rhs) and
                   std::get<3>(_lhs) == std::get<3>(_rhs);
#endif
	}
};


//=== DRIVER CODE

int main()
{
    Account acct("Alex Bastos", 1, 1668, 54321, 1500.f);
    Account myAccounts[] =
    {
        {"Alex Bastos", 1, 1668, 54321, 1500.f},
        {"Aline Souza", 1, 1668, 45794, 530.f},
        {"Cristiano Ronaldo", 13, 557, 87629, 150000.f},
        {"Jose Lima", 18, 331, 1231, 850.f},
        {"Saulo Cunha", 116, 666, 1, 5490.f},
        {"Lima Junior", 12, 123, 5671, 150.f},
        {"Carlito Pardo", 28, 506, 9816, 50.f},
        {"Januario Medeiros", 17, 324, 7777, 4850.f}
    };
    std::cout << ">>> Lista de Contas: " << std::endl;	

    for( auto & e : myAccounts )
        std::cout << e << std::endl;
    std::cout << std::endl;

    // Cria uma tabela de dispersao com capacidade p 23 elementos
    HashTbl< Account::AcctKey, Account, KeyHash, KeyEqual > contas( 4 );

    // Inserindo as contas na tabela hash.
    for( auto & e : myAccounts )
    {
        contas.insert( e.getKey(), e );
        std::cout << ">>> Inserindo \"" << e.mClientName << "\"\n";
        std::cout << ">>> Tabela Hash de Contas depois da insercao: \n"; contas.print();
        // Unit test for insertion
        Account conta_teste;
        contas.retrieve( e.getKey(), conta_teste );
        assert( conta_teste == e );
    }

    std::cout << "\n\n>>> ESTADO FINAL da Tabela Hash de Contas: \n"; contas.print();

    // Em um segundo momento...
    {
        // Testando retrieve.
        Account conta1;

        std::cout << "\n>>> Recuperando dados de \"" << myAccounts[2].mClientName << "\":\n";
        contas.retrieve( myAccounts[2].getKey(), conta1 );
        std::cout << conta1 << std::endl;
        assert( conta1 == myAccounts[2] );
    }
    
    {
        // Testando remove
        Account conta1;

        std::cout << "\n>>> Removendo \"" << myAccounts[2].mClientName << "\":\n";
        contas.remove( myAccounts[2].getKey() );
        std::cout << "\n\n>>> Tabela Hash apos remover: \n"; contas.print();
        assert( contas.retrieve( myAccounts[2].getKey(), conta1 ) == false );
    }
    
    {
        // Testando insert.
        std::cout << "\n>>> Inserindo \"" << myAccounts[2].mClientName << "\":\n";
        contas.insert( myAccounts[2].getKey(), myAccounts[2] );
        std::cout << "\n\n>>> Tabela Hash apos insercao: \n"; contas.print();
    }

    {
        // Testando capacidade de alteração do insert.
        myAccounts[2].mBalance = 40000000.f;
        std::cout << "\n>>> Alterando \"" << myAccounts[2].mClientName << "\":\n";
        contas.insert( myAccounts[2].getKey(), myAccounts[2] );
        std::cout << "\n\n>>> Tabela Hash apos insercao: \n"; contas.print();

        Account conta1;
        contas.retrieve( myAccounts[2].getKey(), conta1 );
        assert( conta1 == myAccounts[2] );
        assert( conta1.mBalance == 40000000.f );
    }

    {
        // Testando clear, empty.
        assert( contas.empty() == false );
        std::cout << "\n>>> Apagando a tabela: \n";
        contas.clear();
        std::cout << "\n\n>>> Tabela Hash apos limpar: \n"; contas.print();
        assert( contas.empty() == true );
    }

    {
        // Testando rehash.
        // Cria uma tabela de dispersao com capacidade p 23 elementos
        HashTbl< Account::AcctKey, Account, KeyHash, KeyEqual > contas( 23 );

        // Inserindo as contas na tabela hash.
        for( auto & e : myAccounts )
        {
            std::cout << ">>> Size = " << contas.count() << std::endl;
            contas.insert( e.getKey(), e );
            std::cout << ">>> Inserindo \"" << e.mClientName << "\"\n";
            std::cout << ">>> Tabela Hash de Contas depois da insercao: \n"; contas.print();
            // Unit test for insertion
            Account conta_teste;
            contas.retrieve( e.getKey(), conta_teste );
            assert( conta_teste == e );
        }
    }

    return EXIT_SUCCESS;
}