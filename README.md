# 3GeoCombine

The title of the manuscript is as follows: Faulted geological contacts: Constraining uncertainty of discontinuity orientation using triangulation and combinatorial algorithm

Co-authors: Michał Michalak a,1; Ryszard Kuzak a,1; Paweł Gładki b; Agnieszka Kulawik c; Yunfeng Ge d 

a Institute of Earth Sciences, Faculty of Natural Sciences, University of Silesia in Katowice,
Będzińska 60, 41-205 Sosnowiec, Poland.
1 Corresponding e-mail address: mimichalak@us.edu.pl.
b Institute of Mathematics, Faculty of Science and Technology, University of Silesia in Katowice,
Bankowa 14, 40-007 Katowice, Poland.
c Faculty of Science and Technology, University of Silesia in Katowice,
Bankowa 14, 40-007 Katowice, Poland.
d Faculty of Engineering, China University of Geosciences, Wuhan, Hubei, China.

Abstract
This study proposes a multi-stage methodology for estimating the orientation of fault planes that influence the geometry of geological contacts. In this methodology, the information about the estimated orientation is assumed to be ultimately used in spatial clustering, i.e., distilling homogenous patterns from data sampled throughout a faulted contact. Orientation data were obtained through applying triangulation on a network of boreholes, and two synthetic models of contacts having approximately two dozen points and a similar number of triangles were created. Based on these models, we demonstrated a substantial limitation of the proposed method for calculating the expected orientation. The discussed limitation follows from the following reason. While triangulated models often decrease the fault dip angle, investigating the variability in dip direction is of greater importance because it is crucial for conducting spatial clustering. To constrain the variability of the triangles’ dip direction, we employed a combinatorial algorithm to get all possible planes from the given point set, which helped achieve greater concentration of observations around the expected dip direction, and produced additionally counterintuitive orientations of the triangles. The discussed singularities were assumed to be geometrical in nature and therefore require special attention. For conducting spatial clustering within faulted contacts, we suggest considering a wider interval of orientations related to faults. This is because these orientations can be genetically related with faults even if they indicate a relatively high directional within-dissimilarity. Statistical methods for circular data were suggested for assessing the confidence intervals.

Description.

In this study, we supply the computational framework that generates four files on the basis of the supplied coordinates of boreholes (see Computer Code Availability for details of required software):
	A .txt file with orientations of triangles corresponding to the triangulation model, which also includes information about the location of selected geometric elements. The process of building the triangulation builds upon the Computational Geometry Algorithms Library (CGAL) which provides access to computational geometry algorithms. Orientation Computing Tool (OCT) software is required.
	A .txt file with orientations of triangles corresponding to all planes that can be generated from all input points, which relates to the combinatorial algorithm for creating all k-element subsets from an n-element set. 3GeoCombine software is required.
	A .vtu file of the triangulation model, which allows the triangulated network of boreholes to be visualized using open-source ParaView software. OCT software is required.
	A .vtu file that contains three-dimensional centers of Delaunay triangles with assigned unit normal vectors. This is also designed for ParaView, and it proved to be particularly useful for sub-vertical planes whose dip direction is difficult to assess visually. OCT software is required.
While the last two files differ in their structure and are not relatively informative to the user, the structure of the first two files is the same and might be of interest to a geological expert. These files contain twenty-two columns that can serve the following purposes: removing collinear configurations, perform stereographic projection in the Dips (Rocscience, 2017) software, or storing the triangulation for subsequent queries. These columns are denoted as follows: X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, X_C, Y_C, Z_C, X_N, Y_N, Z_N, Dip_ang, Dip_dir, DOC, Area, IDT1, IDT2, IDT3. 
The first nine columns are the coordinates of the vertices corresponding to the Delaunay triangles (X1–Z3). To assign normal vectors to the triangles, we computed also their three-dimensional centers (X_C, Y_C, Z_C). The horizontal coordinates (X_C, Y_C) of these centers are also necessary for the assignment of colors associated with orientation domains to the Delaunay triangles. The next three columns are the direction cosines of the computed unit observations (X_N, Y_N, Z_N). This three-dimensional representation can also be expressed as the dip angle and dip direction located in the following two columns, respectively (Dip_ang, Dip_dir). The next two columns can be used to assess the reliability of the results—the coefficient of collinearity and the sizes of the Delaunay triangles (DOC, Area). The final columns (IDT1, IDT2, IDT3) are indices (in the form of integers) of the vertices that were used to build the Delaunay triangles. These indices can be used to run convenient queries involving specific boreholes. For example, the user might need to sub-select all triangles that were dipping to east or these that were built upon a borehole lying within a fault zone.
