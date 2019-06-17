
void removeBad(list<Movie*>& li)
{
	for (list<Movie*>::iterator it = li.begin(); it != li.end();)
	{
		Movie* current = *it;
		if (current->rating() < 55)
		{
			it = li.erase(it);
			delete current;
		}
		else
			it++;
	}
}
