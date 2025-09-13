#pragma once

class CLine
{
public:
	CLine();
	CLine(Vector2& _leftPoint, Vector2& _rIghtPoint);
	~CLine();

public:
	void Render(HDC hDC);

public:
	const LINE& Get_Info() const { return m_tLine; }

private:
	LINE m_tLine;
};
