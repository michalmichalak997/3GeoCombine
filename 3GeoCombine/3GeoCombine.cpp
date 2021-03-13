#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <vector>


using namespace std;

const int n = 3;
const int ROWS = 35000;
const int k_ROWS = 35000;
const int COLS = 3;
const int k_COLS = 3;
const int BUFFSIZE = 80;
double aktu[3];
int total = 0;
const double ratio = 100.00;


int n_comb(int s)
{
	int komb = s;
	for (int i = s; i > s - 2; i--)
	{
		komb = komb * (i - 1);
	}

	return komb / 6;
}

struct Point
{
	int x, y, z;

	Point(int x_1, int x_2, int x_3)
		:x(x_1), y(x_2), z(x_3) {}
};

class plane //a class that stores the crucial figures in terms of computing the orientation
{
public:
	static const int n = 3;			//the dimension of vectors
	const double ex = 2;			//we introduce the restriction of collinearity
	double first_vec[n];            //the first edge of a triangle
	double second_vec[n];			//the second edge of a triangle
	double third_vec[n];			//the third edge of a triangle
	double normal_vec[n];			//normal vector of a triangle
	double directional[n];			//the projection of the normal vector onto the horizontal plane
	double z_axis[n] = { 0,0,1 };   //the definition of the z-axis
	double doc;						//a variable that contains the collinearity coefficient
	double area;					//a variable that stores the area of a triangle
	bool lin_dependence;		    //a bool variable to check to answer whether points are (too) collinear
	string dip_degrees;             //a text variable to store the dip angle
	string azimuth_degrees;         //a text variable to store the dip direction

	double dip_azimuth(double normal[], int n = 2) //a function that computes the dip azimuth
	{
		double coeff = 180 / M_PI;
		double angle = atan2(normal[1], normal[0]);
		angle = angle * coeff;
		if (angle < 0)
		{
			return angle + 360;
		}
		else
		{
			return angle;
		}
	}

	double dip_angle(double z_axis[], double normal_v[]) //function that computes the dip angle
	{
		double angle;
		double expression;
		double coeff = 180 / M_PI;
		expression = abs(dot_product(z_axis, normal_v)) / (length(z_axis) * length(normal_v));
		angle = acos(expression);
		return angle * coeff;
	}

	double dot_product(double vector_line[], double direction[], int n = 3) //function that computes the dot product of vectors
	{
		double product = 0;
		for (int i = 0; i < n; i++)
		{
			product += direction[i] * vector_line[i];
		}
		return product;
	}

	bool dependence(double v1[], double v2[], double v3[]) //function that checks whether the points are collinear
	{
		double len_v1 = length(v1);
		double len_v2 = length(v2);
		double len_v3 = length(v3);
		double lengths[n] = { len_v1, len_v2, len_v3 };

		sort(lengths, lengths + n);
		this->doc = lengths[2] / (lengths[0] + lengths[1]);
		int k = 0;
		for (int i = 0; i < n; i++)
		{
			if (lengths[i] == 0)
			{
				throw runtime_error("Points coincidence");
			}
		}
		if (k != 0)
		{
			return true;
		}
		else
		{
			if (doc > ex)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	double length(double line_vector[], int n = 3) //function that computes the length of a vector
	{
		double vector_length = sqrt(pow(line_vector[0], 2) + pow(line_vector[1], 2) + pow(line_vector[2], 2));
		return vector_length;
	}

	string center(double point_1[], double point_2[], double point_3[]) //function that computes the geometrical centre of a triangle
	{
		double x = (point_1[0] + point_2[0] + point_3[0]) / 300.00;
		double y = (point_1[1] + point_2[1] + point_3[1]) / 300.00;
		return (to_string(x) + ";" + to_string(y));
	}

	plane(double point_1[], double point_2[], double point_3[]) //the class constructor
	{
		double first_try[n];
		double second_try[n];
		double third_try[n];

		for (int i = 0; i < n; i++)
		{
			first_try[i] = point_2[i] - point_1[i];
			second_try[i] = point_3[i] - point_1[i];
			third_try[i] = point_3[i] - point_2[i];
		}

		bool test = dependence(first_try, second_try, third_try);
		if (test == true)
		{
			lin_dependence = true;
		}
		else
		{
			lin_dependence = false;
			for (int i = 0; i < n; i++)
			{
				this->first_vec[i] = first_try[i];
				this->second_vec[i] = second_try[i];
				this->third_vec[i] = third_try[i];
			}
			normal_vec[0] = first_vec[1] * second_vec[2] - second_vec[1] * first_vec[2];
			normal_vec[1] = first_vec[2] * second_vec[0] - second_vec[2] * first_vec[0];
			normal_vec[2] = first_vec[0] * second_vec[1] - second_vec[0] * first_vec[1];

			if (normal_vec[2] < 0) {
				normal_vec[0] *= -1;
				normal_vec[1] *= -1;
				normal_vec[2] *= -1;
			}
			double stala = 0.5;
			double half = stala * (length(first_vec) + length(second_vec) + length(third_vec));
			double s = sqrt(half * (half - length(first_vec)) * (half - length(second_vec)) * (half - length(third_vec)));
			this->area = s * 0.0001;
		}


	}

	string measure()//function that supplies orientation results also for singularities
	{
		if (lin_dependence)
		{
			azimuth_degrees = ("LT");
			dip_degrees = ("LT");
			return (dip_degrees + ";" + azimuth_degrees);
		}
		else if (normal_vec[0] == 0 && normal_vec[1] == 0 && normal_vec[2] != 0)
		{
			dip_degrees = "0";
			azimuth_degrees = ("x");
			return (dip_degrees + ";" + azimuth_degrees);
		}
		else if (normal_vec[2] == 0)
		{
			dip_degrees = "90";
			azimuth_degrees = to_string(dip_azimuth(normal_vec));
			return dip_degrees + ";" + azimuth_degrees;
		}
		else
		{
			double dipping_angle = dip_angle(z_axis, normal_vec);
			dip_degrees = to_string(dipping_angle);
			azimuth_degrees = to_string(dip_azimuth(normal_vec));
			return dip_degrees + ";" + azimuth_degrees;
		}
	}
};

int main()
{
	int n_boreholes;

	cout << "Type in the number of boreholes" << endl;
	cin >> n_boreholes; cout << "\n";

	cout << "You will get: " << n_comb(n_boreholes) << " observations" << endl;

	if (n_boreholes < 0) { cout << "Not true!" << "\n"; }
	else
	{

		try
		{
			double tablica[ROWS][COLS] = { 0 };
			int row = 0, col;
			char buff[BUFFSIZE];

			string path_i, path_o;

			cout << "Type in the path of your input data:" << endl; //the user is required to type in the input path
			cout << "Example: C:\\dev\\CGAL-4.8\\examples\\Triangulation_2\\JurassicBottomInput.txt" << endl << endl;
			cin >> path_i;

			ifstream download(path_i);
			if (!download) cout << "Error in opening file" << endl; //the case when the file cannot be uploaded

			cout << "Type in the path of the output:" << endl; //the user is required to type in the output path
			cout << "Example: C:\\dev\\CGAL-4.8\\examples\\Triangulation_2\\JurassicBottomOutput.txt" << endl << endl;
			cin >> path_o;

			string tempor;//a temporary variable storing figures while uploading
			stringstream ss;

			vector <Point> pits;

			while (download.getline(buff, BUFFSIZE) && row < ROWS)
			{
				// copy the entire buffered line into the stringstream
				ss << buff;
				col = 0;
				while (ss.getline(buff, 40, ',') && col < COLS)
				{
					tablica[row][col] = atoi(buff);
					++col;
				}
				ss << "";
				ss.clear();
				++row;
			}
			download.close();

			cout << "\n";
			int k = 0;

			ofstream all(path_o);

			all << "X1" << ';' << "Y1" << ';' << "Z1" << ';' << "X2" << ';' <<
				"Y2" << ';' << "Z2" << ';' << "X3" << ';' << "Y3" << ';' << "Z3"
				<< ';' << "X_C" << ";" << "Y_C" << ";" << "X_N" << ";" << "Y_N"
				<< ";" << "Z_N" << ";" << "Dip_ang" << ';' << "Dip_dir" <<
				";" << "DOC" << ";" << "Area" << "\n";
			const int g = 3;

			int l_komb = n_comb(n_boreholes);


			while ((2 + k) <= l_komb - 1)
			{
				int S[g];
				for (int i = 0; i < g; i++) S[i] = i;

				int p = g - 1;

				while (p >= 0)
				{
					double point_1[] = { tablica[S[0]][0], tablica[S[0]][1], tablica[S[0]][2] };
					double point_2[] = { tablica[S[1]][0], tablica[S[1]][1], tablica[S[1]][2] };
					double point_3[] = { tablica[S[2]][0], tablica[S[2]][1], tablica[S[2]][2] };

					plane current_plane = plane(point_1, point_2, point_3);					//constructing a plane that is processed at the moment
					string result = current_plane.measure();								//extracting the dip angle and the dip direction
					string centroid = current_plane.center(point_1, point_2, point_3);

					double x_n = current_plane.normal_vec[0]; //extracting coordinates of the normal vector of a planar Delaunay triangle
					double y_n = current_plane.normal_vec[1];
					double z_n = current_plane.normal_vec[2];

					x_n = x_n / current_plane.length(current_plane.normal_vec);
					y_n = y_n / current_plane.length(current_plane.normal_vec);
					z_n = z_n / current_plane.length(current_plane.normal_vec);

					all << to_string(point_1[0] / ratio) << ";" << to_string(point_1[1] / ratio) << ";" << to_string(point_1[2] / ratio) << ";" << //saving orientation elements with respect to the column names
						to_string(point_2[0] / ratio) << ";" << to_string(point_2[1] / ratio) << ";" << to_string(point_2[2] / ratio) << ";" <<
						to_string(point_3[0] / ratio) << ";" << to_string(point_3[1] / ratio) << ";" << to_string(point_3[2] / ratio) << ";" <<
						centroid << ";" << x_n << ";" << y_n << ";" << z_n << ";" << result << ";" << current_plane.doc << ";" << current_plane.area <<
						endl;

					k = k + 3;

					cout << "\n";
					if (S[g - 1] == n_boreholes - 1) { p--; }
					else { p = g - 1; }
					if (p >= 0)
					{
						for (int i = g - 1; i >= p; i--)
						{
							S[i] = S[p] + i - p + 1;
						}
					}
					::total++;
				}
			}
			all.close();

		}
		catch (runtime_error e)
		{

			cout << "Runtime error: " << e.what();
		}
	}
	system("PAUSE");
	return 0;
}