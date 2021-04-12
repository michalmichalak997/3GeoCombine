# 3GeoCombine

# Title
Constraining uncertainty of fault orientation using a combinatorial algorithm

# Co-authors

Michał Michalak a,b,1; Ryszard Kuzak a,1; Paweł Gładki c; Agnieszka Kulawik d; Yunfeng Ge e

a: Institute of Earth Sciences, Faculty of Natural Sciences, University of Silesia in Katowice, Będzińska 60, 41-205 Sosnowiec, Poland.

b: AGH University of Technology in Kraków, al. Mickiewicza 30, Kraków, Poland.

1: Corresponding e-mail address: mimichalak@us.edu.pl.

c: Institute of Mathematics, Faculty of Science and Technology, University of Silesia in Katowice, Bankowa 14, 40-007 Katowice, Poland.

d: Faculty of Science and Technology, University of Silesia in Katowice, Bankowa 14, 40-007 Katowice, Poland.

e: Faculty of Engineering, China University of Geosciences, Wuhan, Hubei, China.

# Abstract
This study presents experimental results from assessing fault orientation using
triangulation and a combinatorial algorithm. We constructed two geological surfaces
with vertical and inclined faults. These surfaces were documented by boreholes and
represented by triangulated surfaces. We first calculated orientations for a small
sample of triangles genetically related to faults that were also members of the
Delaunay triangulation. To reduce the epistemic uncertainty regarding the true fault
strike, we applied a combinatorial algorithm that allowed us to investigate the
orientation distribution of all planes genetically related to the fault. The experiment
revealed three unintuitive effects that require further studies: 1) greater concentration
of observations about the true dip direction; 2) the same dip direction for different
triangles; and 3) triangles that dip in the opposite direction to the fault. To conduct
spatial clustering within surfaces, we suggest considering a broader interval of
orientations related to faults. This broader interval serves to honor the observation that
orientations can be genetically related to faults, even if they indicate a relatively high
directional within-dissimilarity. We suggest statistical methods for circular data to
investigate the resulting distributions. The computer code associated with this study is
open source and freely available.

# Software description
## How to use the program?
You only need to specify the path for the input and output files:
![image](https://user-images.githubusercontent.com/28152295/114365407-bd596580-9b7a-11eb-968e-b21fca674854.png)

## How to prepare the input data?
In the input file, each line refers to one borehole. The XYZ coordinates are separated by space.
![image](https://user-images.githubusercontent.com/28152295/114365609-eb3eaa00-9b7a-11eb-9604-aeeb6ee42313.png)

## Further description
In this study, we supply the computational framework that generates four files on the basis of the supplied coordinates of boreholes (see Computer Code Availability for details of required software):
	A .txt file with orientations of triangles corresponding to the triangulation model, which also includes information about the location of selected geometric elements. The process of building the triangulation builds upon the Computational Geometry Algorithms Library (CGAL) which provides access to computational geometry algorithms. Orientation Computing Tool (OCT) software is required.
	A .txt file with orientations of triangles corresponding to all planes that can be generated from all input points, which relates to the combinatorial algorithm for creating all k-element subsets from an n-element set. 3GeoCombine software is required.
	A .vtu file of the triangulation model, which allows the triangulated network of boreholes to be visualized using open-source ParaView software. OCT software is required.
	A .vtu file that contains three-dimensional centers of Delaunay triangles with assigned unit normal vectors. This is also designed for ParaView, and it proved to be particularly useful for sub-vertical planes whose dip direction is difficult to assess visually. OCT software is required.
While the last two files differ in their structure and are not relatively informative to the user, the structure of the first two files is the same and might be of interest to a geological expert. These files contain twenty-two columns that can serve the following purposes: removing collinear configurations, perform stereographic projection in the Dips (Rocscience, 2017) software, or storing the triangulation for subsequent queries. These columns are denoted as follows: X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, X_C, Y_C, Z_C, X_N, Y_N, Z_N, Dip_ang, Dip_dir, DOC, Area, IDT1, IDT2, IDT3. 
The first nine columns are the coordinates of the vertices corresponding to the Delaunay triangles (X1–Z3). To assign normal vectors to the triangles, we computed also their three-dimensional centers (X_C, Y_C, Z_C). The horizontal coordinates (X_C, Y_C) of these centers are also necessary for the assignment of colors associated with orientation domains to the Delaunay triangles. The next three columns are the direction cosines of the computed unit observations (X_N, Y_N, Z_N). This three-dimensional representation can also be expressed as the dip angle and dip direction located in the following two columns, respectively (Dip_ang, Dip_dir). The next two columns can be used to assess the reliability of the results—the coefficient of collinearity and the sizes of the Delaunay triangles (DOC, Area). The final columns (IDT1, IDT2, IDT3) are indices (in the form of integers) of the vertices that were used to build the Delaunay triangles. These indices can be used to run convenient queries involving specific boreholes. For example, the user might need to sub-select all triangles that were dipping to east or these that were built upon a borehole lying within a fault zone.
