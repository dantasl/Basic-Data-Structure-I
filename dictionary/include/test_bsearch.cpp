int _search ( const int & _x ) const
			{
				KeyComparator comp;
				int left(0);
				int right( DAL<Key, Data, KeyComparator>::mi_Length );
				int mid(0);
				
				while ( left <= right )
				{
					mid = (left + right) / 2;
					auto data = DAL<Key, Data, KeyComparator>::mpt_Data[mid].id;
					if ( not comp(data, _x) and not comp(_x, data)	)
						return data;
					if ( comp(data, _x) ) left = mid + 1;
					else right = mid - 1;
				}

				return -1;	
			}