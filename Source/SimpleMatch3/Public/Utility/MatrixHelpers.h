#pragma once
#include <vector>

#include "TestMacros.h"

namespace MatrixHelpers
{
	using namespace std;

	inline vector<vector<int8>> RotateMatrixAnticlockwise(const vector<vector<int8>>& OldMatrix)
	{
		const size_t OldMatrixRowCount = OldMatrix.size();
		const size_t OldMatrixColumnCount = OldMatrix[0].size();
		vector<vector<int8>> NewMatrix(OldMatrixColumnCount, vector<int8>(OldMatrixRowCount));

		int NewColumn = 0;
		int NewRow = 0;

		for (int OldColumn = OldMatrixColumnCount - 1; OldColumn >= 0; OldColumn--)
		{
			NewColumn = 0;
			for (int OldRow = 0; OldRow < OldMatrixRowCount; OldRow++)
			{
				NewMatrix[NewRow][NewColumn] = OldMatrix[OldRow][OldColumn];
				NewColumn++;
			}
			NewRow++;
		}

		FString string("Anticlockwise RotateMatrix \n");
		for (int i = 0; i < NewMatrix.size(); ++i)
		{
			for (int j = 0; j < NewMatrix[0].size(); ++j)
			{
				string.AppendInt(NewMatrix[i][j]);
			}
			string.Append("\n");
		}
		DEBUG(TEXT("%s"), *string);
		
		return NewMatrix;
	}
	
	inline FMatchMatrix RotateMatrixAnticlockwise(const FMatchMatrix OldMatrix)
	{
		const size_t OldMatrixRowCount = OldMatrix.Rows.Num();
		const size_t OldMatrixColumnCount = OldMatrix.Rows[0].Elements.Num();
		FMatchMatrix NewMatrix(OldMatrixColumnCount, OldMatrixRowCount);
	
		int NewColumn = 0;
		int NewRow = 0;
	
		for (int OldColumn = OldMatrixColumnCount - 1; OldColumn >= 0; OldColumn--)
		{
			NewColumn = 0;
			for (int OldRow = 0; OldRow < OldMatrixRowCount; OldRow++)
			{
				NewMatrix.Rows[NewRow].Elements[NewColumn] = OldMatrix.Rows[OldRow].Elements[OldColumn];
				NewColumn++;
			}
			NewRow++;
		}
		
		return NewMatrix;
	}
	
	inline void DebugLogMatrix(const FMatchMatrix* Matrix)
	{
		FString string("DebugFMatrix -- \n");
		for (int i = 0; i < Matrix->Rows.Num(); ++i)
		{
			for (int j = 0; j < Matrix->Rows[0].Elements.Num(); ++j)
			{
				string.AppendInt(Matrix->Rows[i].Elements[j]);
			}
			string.Append("\n");
		}
		DEBUG(TEXT("%s"), *string);
	}
	
};
