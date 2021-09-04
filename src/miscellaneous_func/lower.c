//asuming aschii , converts capital alphbet to lover case
char lower(char ch)
{
	return (ch >= 'A' && ch <= 'Z') ? (ch + 'a' - 'A') : ch;
}
