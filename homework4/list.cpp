
void listAll(const Domain* d, string path) // two-parameter overload
{
	if (d->subdomains().size() == 0)
	{
		cout << path << endl;
		return;
	}
	for (vector<Domain*>::const_iterator it = d->subdomains().begin(); it != d->subdomains().end(); it++)
	{
		const Domain* m_domain = *it;
		string m_path = "";
		if (path.size() != 0)
		    m_path = m_domain->label() + '.' + path;
		else
			m_path = m_domain->label() + path;
		listAll(m_domain, m_path);
	}

}
\