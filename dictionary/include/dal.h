#ifndef _DAL_H_
#define _DAL_H_

namespace ac
{
	template< typename Key, typename Data, typename KeyComparator = std::less<Key> >
	class DAL
	{
		protected:
			
			struct NodeAL // Node structure representing pair key-information
			{
				Key id; // The key is a simple integer
				Data info; // The information is a chain of chars
			};

			static const int SIZE=50; // Defaul list size
			int mi_Length;			  // Current lenght of the list
			int mi_Capacity;		  // Maximum storage capacity
			NodeAL *mpt_Data;			  // Storage area: dinamic allocated array

			// Auxiliar search
			int _search ( const Key & _x ) const
			{
				KeyComparator comp;

				for(auto i(0); i < mi_Length; ++i)
				{
					if( not comp( mpt_Data[i].id, _x ) and not comp( _x, mpt_Data[i].id )  )
						return i;
				}
				return -1; 
			}

			public:
				
				DAL ( int _MaxSz = SIZE )
					: mi_Length(0)
					, mi_Capacity(_MaxSz)
					, mpt_Data( new NodeAL[_MaxSz] )
					{ /* empty */ }
				
				virtual ~DAL () { delete [] mpt_Data; }

				int capacity( void )
				{
					return mi_Capacity;
				}

				bool remove ( const Key & _x, Data & _s ) // perguntar a selan se deixa o buraco ou não
				{
					if ( mi_Length == 0 ) return false;
					auto found_position = _search(_x);
					if ( found_position == -1 ) return false;

					return true;
				}
				
				bool search ( const Key & _x, Data & _s ) const
				{
					//Check if table is empty;
					if ( mi_Length == 0 ) return false;

					auto found_position = _search(_x);

					if ( found_position == -1 ) return false;
					_s = mpt_Data[found_position].info;
					return true;
				}
				
				bool insert ( const Key & _newKey, const Data & _newInfo )
				{
					// Checks if the dictionary can store new data
					if ( mi_Length == mi_Capacity ) return false;

					// Iterates over the array checking if the client's input is unique
					for (auto i(0); i < mi_Length; ++i)
						if ( mpt_Data[i].id == _newKey ) return false;

					// Reaching here, the input is valid to be inserted
					mpt_Data[mi_Length].id = _newKey;
					mpt_Data[mi_Length].info = _newInfo;
					mi_Length++;

					return true;
				}
				
				Key min () const;
				Key max () const;
				bool sucessor ( const Key & _x, Key & _y ) const;
				bool predecessor ( const Key _x, Key & _y ) const;

				inline friend
				std::ostream &operator<< ( std::ostream& _os, const DAL& _oList )
				{
					_os << "[ ";
					for( int i(0); i < _oList.mi_Length; ++i )
						_os << "{id: " << _oList.mpt_Data[i].id << ", info: "
							<< _oList.mpt_Data[i].info << "} ";
					_os << "]";
					return _os;		
				} 
	};
}

#endif