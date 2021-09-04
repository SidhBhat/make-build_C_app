// function to round 'input' to nearest integer
int Int_Round(float input)
{
	if(input - (int)input < 0.5f)
		return (int)input;
	else
		return (int)input + 1;
}
