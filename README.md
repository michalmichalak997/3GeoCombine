# 3GeoCombine

# Title
Constraining uncertainty of fault orientation using a combinatorial algorithm

# Co-authors

Michał Michalak a,b,1; Ryszard Kuzak a; Paweł Gładki c; Agnieszka Kulawik d; Yunfeng Ge e

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

## Output
The first nine columns are the coordinates of the vertices corresponding to the Delaunay triangles (X1–Z3). To assign normal vectors to the triangles, we computed also their three-dimensional centers (X_C, Y_C, Z_C). The horizontal coordinates (X_C, Y_C) of these centers are also necessary for the assignment of colors associated with orientation domains to the Delaunay triangles. The next three columns are the direction cosines of the computed unit observations (X_N, Y_N, Z_N). This three-dimensional representation can also be expressed as the dip angle and dip direction located in the following two columns, respectively (Dip_ang, Dip_dir). The next two columns can be used to assess the reliability of the results—the coefficient of collinearity and the sizes of the Delaunay triangles (DOC, Area).

## Supplementary software

If you want to obtain orientations from Delaunay triangulation, please use Orientation Computing Tool.

