=== Run information ===

Scheme:weka.classifiers.trees.J48 -C 0.25 -M 2
Relation:     newinfo-weka.filters.unsupervised.attribute.Remove-R1
Instances:    358
Attributes:   22
              Max TemperatureF
              Mean TemperatureF
              Min TemperatureF
              Max Dew PointF
              MeanDew PointF
              Min DewpointF
              Max Humidity
              Mean Humidity
              Min Humidity
              Max Sea Level PressureIn
              Mean Sea Level PressureIn
              Min Sea Level PressureIn
              Max VisibilityMiles
              Mean VisibilityMiles
              Min VisibilityMiles
              Max Wind SpeedMPH
              Mean Wind SpeedMPH
              Max Gust SpeedMPH
              PrecipitationIn
              CloudCover
              Events
              WindDirDegrees
Test mode:10-fold cross-validation

=== Classifier model (full training set) ===

J48 pruned tree
------------------

Max TemperatureF <= 44
|   Max Wind SpeedMPH <= 9
|   |   Min Humidity <= 59: Fog-Rain (4.0/1.0)
|   |   Min Humidity > 59: Fog-Rain-Snow (2.0/1.0)
|   Max Wind SpeedMPH > 9
|   |   Min Humidity <= 20: Rain (2.0)
|   |   Min Humidity > 20
|   |   |   Max Sea Level PressureIn <= 30.46
|   |   |   |   Min TemperatureF <= 30: NoEvent (49.0/10.0)
|   |   |   |   Min TemperatureF > 30
|   |   |   |   |   Max Humidity <= 57: Snow (2.0)
|   |   |   |   |   Max Humidity > 57
|   |   |   |   |   |   Min DewpointF <= 21: NoEvent (2.0)
|   |   |   |   |   |   Min DewpointF > 21: Fog-Snow (2.0)
|   |   |   Max Sea Level PressureIn > 30.46
|   |   |   |   Mean Humidity <= 64: NoEvent (13.0/3.0)
|   |   |   |   Mean Humidity > 64: Rain-Snow (3.0/1.0)
Max TemperatureF > 44
|   Max VisibilityMiles <= 9
|   |   Min VisibilityMiles <= 3: Rain (12.0)
|   |   Min VisibilityMiles > 3
|   |   |   Mean Humidity <= 69: Fog-Rain (3.0/1.0)
|   |   |   Mean Humidity > 69: NoEvent (2.0)
|   Max VisibilityMiles > 9
|   |   Min Humidity <= 61
|   |   |   Mean Wind SpeedMPH <= 5
|   |   |   |   Min DewpointF <= 21
|   |   |   |   |   Max Dew PointF <= 38
|   |   |   |   |   |   Min Sea Level PressureIn <= 30.06: NoEvent (4.0)
|   |   |   |   |   |   Min Sea Level PressureIn > 30.06: Rain (2.0)
|   |   |   |   |   Max Dew PointF > 38: Rain (7.0)
|   |   |   |   Min DewpointF > 21
|   |   |   |   |   WindDirDegrees <= 79: NoEvent (25.0/2.0)
|   |   |   |   |   WindDirDegrees > 79
|   |   |   |   |   |   Mean Wind SpeedMPH <= 3
|   |   |   |   |   |   |   Min TemperatureF <= 68
|   |   |   |   |   |   |   |   Mean VisibilityMiles <= 8: NoEvent (8.0/2.0)
|   |   |   |   |   |   |   |   Mean VisibilityMiles > 8
|   |   |   |   |   |   |   |   |   Min DewpointF <= 53
|   |   |   |   |   |   |   |   |   |   Min VisibilityMiles <= 8: Rain (5.0)
|   |   |   |   |   |   |   |   |   |   Min VisibilityMiles > 8
|   |   |   |   |   |   |   |   |   |   |   CloudCover <= 3: NoEvent (8.0)
|   |   |   |   |   |   |   |   |   |   |   CloudCover > 3: Rain (3.0/1.0)
|   |   |   |   |   |   |   |   |   Min DewpointF > 53
|   |   |   |   |   |   |   |   |   |   Max Sea Level PressureIn <= 30.15: NoEvent (3.0)
|   |   |   |   |   |   |   |   |   |   Max Sea Level PressureIn > 30.15: Fog-Rain (2.0)
|   |   |   |   |   |   |   Min TemperatureF > 68: Rain (5.0)
|   |   |   |   |   |   Mean Wind SpeedMPH > 3
|   |   |   |   |   |   |   CloudCover <= 3
|   |   |   |   |   |   |   |   Min VisibilityMiles <= 2: Rain (3.0)
|   |   |   |   |   |   |   |   Min VisibilityMiles > 2
|   |   |   |   |   |   |   |   |   Min Sea Level PressureIn <= 29.62: Rain (3.0)
|   |   |   |   |   |   |   |   |   Min Sea Level PressureIn > 29.62
|   |   |   |   |   |   |   |   |   |   WindDirDegrees <= 210
|   |   |   |   |   |   |   |   |   |   |   Min Sea Level PressureIn <= 30.18: Rain (5.0)
|   |   |   |   |   |   |   |   |   |   |   Min Sea Level PressureIn > 30.18: NoEvent (3.0)
|   |   |   |   |   |   |   |   |   |   WindDirDegrees > 210: NoEvent (49.0/9.0)
|   |   |   |   |   |   |   CloudCover > 3: NoEvent (18.0/3.0)
|   |   |   Mean Wind SpeedMPH > 5
|   |   |   |   Mean Humidity <= 67: NoEvent (61.0/6.0)
|   |   |   |   Mean Humidity > 67
|   |   |   |   |   CloudCover <= 3: Fog-Rain (3.0/1.0)
|   |   |   |   |   CloudCover > 3
|   |   |   |   |   |   WindDirDegrees <= 222: Rain (6.0/1.0)
|   |   |   |   |   |   WindDirDegrees > 222: NoEvent (6.0)
|   |   Min Humidity > 61
|   |   |   Mean Sea Level PressureIn <= 29.75: Rain-Snow (2.0)
|   |   |   Mean Sea Level PressureIn > 29.75
|   |   |   |   WindDirDegrees <= 194
|   |   |   |   |   CloudCover <= 6
|   |   |   |   |   |   Mean Wind SpeedMPH <= 2: Rain (3.0)
|   |   |   |   |   |   Mean Wind SpeedMPH > 2
|   |   |   |   |   |   |   Max Gust SpeedMPH <= 19: NoEvent (4.0/1.0)
|   |   |   |   |   |   |   Max Gust SpeedMPH > 19: Fog-Rain (4.0)
|   |   |   |   |   CloudCover > 6: Rain (12.0/3.0)
|   |   |   |   WindDirDegrees > 194: NoEvent (8.0/2.0)

Number of Leaves  : 	39

Size of the tree : 	77


Time taken to build model: 0.05 seconds

=== Stratified cross-validation ===
=== Summary ===

Correctly Classified Instances         202               56.4246 %
Incorrectly Classified Instances       156               43.5754 %
Kappa statistic                          0.1044
Mean absolute error                      0.1208
Root mean squared error                  0.3094
Relative absolute error                 88.9197 %
Root relative squared error            119.5701 %
Total Number of Instances              358     

=== Detailed Accuracy By Class ===

               TP Rate   FP Rate   Precision   Recall  F-Measure   ROC Area  Class
                 0.77      0.672      0.673     0.77      0.718      0.566    NoEvent
                 0         0.057      0         0         0          0.503    Fog-Rain
                 0.312     0.135      0.387     0.312     0.345      0.585    Rain
                 0         0          0         0         0          0.494    Fog
                 0         0.009      0         0         0          0.568    Rain-Snow
                 0         0.014      0         0         0          0.635    Fog-Snow
                 0         0.011      0         0         0          0.632    Fog-Rain-Snow
                 0.167     0.003      0.5       0.167     0.25       0.603    Snow
Weighted Avg.    0.564     0.465      0.524     0.564     0.54       0.568

=== Confusion Matrix ===

   a   b   c   d   e   f   g   h   <-- classified as
 177  13  32   0   2   3   2   1 |   a = NoEvent
  19   0   2   0   1   1   1   0 |   b = Fog-Rain
  49   3  24   0   0   1   0   0 |   c = Rain
   0   1   1   0   0   0   0   0 |   d = Fog
   5   0   1   0   0   0   1   0 |   e = Rain-Snow
   5   0   1   0   0   0   0   0 |   f = Fog-Snow
   5   1   0   0   0   0   0   0 |   g = Fog-Rain-Snow
   3   1   1   0   0   0   0   1 |   h = Snow

=== Source code ===

// Generated with Weka 3.6.6
//
// This code is public domain and comes with no warranty.
//
// Timestamp: Sat May 03 12:51:20 EDT 2014

package weka.classifiers;

import weka.core.Attribute;
import weka.core.Capabilities;
import weka.core.Capabilities.Capability;
import weka.core.Instance;
import weka.core.Instances;
import weka.core.RevisionUtils;
import weka.classifiers.Classifier;

public class WekaWrapper
  extends Classifier {

  /**
   * Returns only the toString() method.
   *
   * @return a string describing the classifier
   */
  public String globalInfo() {
    return toString();
  }

  /**
   * Returns the capabilities of this classifier.
   *
   * @return the capabilities
   */
  public Capabilities getCapabilities() {
    weka.core.Capabilities result = new weka.core.Capabilities(this);

    result.enable(weka.core.Capabilities.Capability.NOMINAL_ATTRIBUTES);
    result.enable(weka.core.Capabilities.Capability.NUMERIC_ATTRIBUTES);
    result.enable(weka.core.Capabilities.Capability.DATE_ATTRIBUTES);
    result.enable(weka.core.Capabilities.Capability.MISSING_VALUES);
    result.enable(weka.core.Capabilities.Capability.NOMINAL_CLASS);
    result.enable(weka.core.Capabilities.Capability.MISSING_CLASS_VALUES);

    result.setMinimumNumberInstances(0);

    return result;
  }

  /**
   * only checks the data against its capabilities.
   *
   * @param i the training data
   */
  public void buildClassifier(Instances i) throws Exception {
    // can classifier handle the data?
    getCapabilities().testWithFail(i);
  }

  /**
   * Classifies the given instance.
   *
   * @param i the instance to classify
   * @return the classification result
   */
  public double classifyInstance(Instance i) throws Exception {
    Object[] s = new Object[i.numAttributes()];
    
    for (int j = 0; j < s.length; j++) {
      if (!i.isMissing(j)) {
        if (i.attribute(j).isNominal())
          s[j] = new String(i.stringValue(j));
        else if (i.attribute(j).isNumeric())
          s[j] = new Double(i.value(j));
      }
    }
    
    // set class value to missing
    s[i.classIndex()] = null;
    
    return WekaClassifier.classify(s);
  }

  /**
   * Returns the revision string.
   * 
   * @return        the revision
   */
  public String getRevision() {
    return RevisionUtils.extract("1.0");
  }

  /**
   * Returns only the classnames and what classifier it is based on.
   *
   * @return a short description
   */
  public String toString() {
    return "Auto-generated classifier wrapper, based on weka.classifiers.trees.J48 (generated with Weka 3.6.6).\n" + this.getClass().getName() + "/WekaClassifier";
  }

  /**
   * Runs the classfier from commandline.
   *
   * @param args the commandline arguments
   */
  public static void main(String args[]) {
    runClassifier(new WekaWrapper(), args);
  }
}

class WekaClassifier {

  public static double classify(Object[] i)
    throws Exception {

    double p = Double.NaN;
    p = WekaClassifier.N7cfd14be0(i);
    return p;
  }
  static double N7cfd14be0(Object []i) {
    double p = Double.NaN;
    if (i[0] == null) {
      p = 0;
    } else if (((Double) i[0]).doubleValue() <= 44.0) {
    p = WekaClassifier.N4b5d060d1(i);
    } else if (((Double) i[0]).doubleValue() > 44.0) {
    p = WekaClassifier.N64cd0469(i);
    } 
    return p;
  }
  static double N4b5d060d1(Object []i) {
    double p = Double.NaN;
    if (i[15] == null) {
      p = 1;
    } else if (((Double) i[15]).doubleValue() <= 9.0) {
    p = WekaClassifier.N483866222(i);
    } else if (((Double) i[15]).doubleValue() > 9.0) {
    p = WekaClassifier.N6eb967383(i);
    } 
    return p;
  }
  static double N483866222(Object []i) {
    double p = Double.NaN;
    if (i[8] == null) {
      p = 1;
    } else if (((Double) i[8]).doubleValue() <= 59.0) {
      p = 1;
    } else if (((Double) i[8]).doubleValue() > 59.0) {
      p = 6;
    } 
    return p;
  }
  static double N6eb967383(Object []i) {
    double p = Double.NaN;
    if (i[8] == null) {
      p = 2;
    } else if (((Double) i[8]).doubleValue() <= 20.0) {
      p = 2;
    } else if (((Double) i[8]).doubleValue() > 20.0) {
    p = WekaClassifier.N4e27c6524(i);
    } 
    return p;
  }
  static double N4e27c6524(Object []i) {
    double p = Double.NaN;
    if (i[9] == null) {
      p = 0;
    } else if (((Double) i[9]).doubleValue() <= 30.46) {
    p = WekaClassifier.N154d59945(i);
    } else if (((Double) i[9]).doubleValue() > 30.46) {
    p = WekaClassifier.N1fa4f2fd8(i);
    } 
    return p;
  }
  static double N154d59945(Object []i) {
    double p = Double.NaN;
    if (i[2] == null) {
      p = 0;
    } else if (((Double) i[2]).doubleValue() <= 30.0) {
      p = 0;
    } else if (((Double) i[2]).doubleValue() > 30.0) {
    p = WekaClassifier.N9340e796(i);
    } 
    return p;
  }
  static double N9340e796(Object []i) {
    double p = Double.NaN;
    if (i[6] == null) {
      p = 7;
    } else if (((Double) i[6]).doubleValue() <= 57.0) {
      p = 7;
    } else if (((Double) i[6]).doubleValue() > 57.0) {
    p = WekaClassifier.N38a22ea77(i);
    } 
    return p;
  }
  static double N38a22ea77(Object []i) {
    double p = Double.NaN;
    if (i[5] == null) {
      p = 0;
    } else if (((Double) i[5]).doubleValue() <= 21.0) {
      p = 0;
    } else if (((Double) i[5]).doubleValue() > 21.0) {
      p = 5;
    } 
    return p;
  }
  static double N1fa4f2fd8(Object []i) {
    double p = Double.NaN;
    if (i[7] == null) {
      p = 0;
    } else if (((Double) i[7]).doubleValue() <= 64.0) {
      p = 0;
    } else if (((Double) i[7]).doubleValue() > 64.0) {
      p = 4;
    } 
    return p;
  }
  static double N64cd0469(Object []i) {
    double p = Double.NaN;
    if (i[12] == null) {
      p = 2;
    } else if (((Double) i[12]).doubleValue() <= 9.0) {
    p = WekaClassifier.N1cfda6e510(i);
    } else if (((Double) i[12]).doubleValue() > 9.0) {
    p = WekaClassifier.N19d839de12(i);
    } 
    return p;
  }
  static double N1cfda6e510(Object []i) {
    double p = Double.NaN;
    if (i[14] == null) {
      p = 2;
    } else if (((Double) i[14]).doubleValue() <= 3.0) {
      p = 2;
    } else if (((Double) i[14]).doubleValue() > 3.0) {
    p = WekaClassifier.N50d8134111(i);
    } 
    return p;
  }
  static double N50d8134111(Object []i) {
    double p = Double.NaN;
    if (i[7] == null) {
      p = 1;
    } else if (((Double) i[7]).doubleValue() <= 69.0) {
      p = 1;
    } else if (((Double) i[7]).doubleValue() > 69.0) {
      p = 0;
    } 
    return p;
  }
  static double N19d839de12(Object []i) {
    double p = Double.NaN;
    if (i[8] == null) {
      p = 0;
    } else if (((Double) i[8]).doubleValue() <= 61.0) {
    p = WekaClassifier.N42bf2b1313(i);
    } else if (((Double) i[8]).doubleValue() > 61.0) {
    p = WekaClassifier.N6b02b23d33(i);
    } 
    return p;
  }
  static double N42bf2b1313(Object []i) {
    double p = Double.NaN;
    if (i[16] == null) {
      p = 0;
    } else if (((Double) i[16]).doubleValue() <= 5.0) {
    p = WekaClassifier.N14a50ea114(i);
    } else if (((Double) i[16]).doubleValue() > 5.0) {
    p = WekaClassifier.N14c8249330(i);
    } 
    return p;
  }
  static double N14a50ea114(Object []i) {
    double p = Double.NaN;
    if (i[5] == null) {
      p = 2;
    } else if (((Double) i[5]).doubleValue() <= 21.0) {
    p = WekaClassifier.N6063769d15(i);
    } else if (((Double) i[5]).doubleValue() > 21.0) {
    p = WekaClassifier.N4a6dfd4d17(i);
    } 
    return p;
  }
  static double N6063769d15(Object []i) {
    double p = Double.NaN;
    if (i[3] == null) {
      p = 0;
    } else if (((Double) i[3]).doubleValue() <= 38.0) {
    p = WekaClassifier.N22006edb16(i);
    } else if (((Double) i[3]).doubleValue() > 38.0) {
      p = 2;
    } 
    return p;
  }
  static double N22006edb16(Object []i) {
    double p = Double.NaN;
    if (i[11] == null) {
      p = 0;
    } else if (((Double) i[11]).doubleValue() <= 30.06) {
      p = 0;
    } else if (((Double) i[11]).doubleValue() > 30.06) {
      p = 2;
    } 
    return p;
  }
  static double N4a6dfd4d17(Object []i) {
    double p = Double.NaN;
    if (i[21] == null) {
      p = 0;
    } else if (((Double) i[21]).doubleValue() <= 79.0) {
      p = 0;
    } else if (((Double) i[21]).doubleValue() > 79.0) {
    p = WekaClassifier.N7b10f06718(i);
    } 
    return p;
  }
  static double N7b10f06718(Object []i) {
    double p = Double.NaN;
    if (i[16] == null) {
      p = 0;
    } else if (((Double) i[16]).doubleValue() <= 3.0) {
    p = WekaClassifier.N1517395019(i);
    } else if (((Double) i[16]).doubleValue() > 3.0) {
    p = WekaClassifier.N5d711c2c25(i);
    } 
    return p;
  }
  static double N1517395019(Object []i) {
    double p = Double.NaN;
    if (i[2] == null) {
      p = 0;
    } else if (((Double) i[2]).doubleValue() <= 68.0) {
    p = WekaClassifier.N27b3be0120(i);
    } else if (((Double) i[2]).doubleValue() > 68.0) {
      p = 2;
    } 
    return p;
  }
  static double N27b3be0120(Object []i) {
    double p = Double.NaN;
    if (i[13] == null) {
      p = 0;
    } else if (((Double) i[13]).doubleValue() <= 8.0) {
      p = 0;
    } else if (((Double) i[13]).doubleValue() > 8.0) {
    p = WekaClassifier.N97f480421(i);
    } 
    return p;
  }
  static double N97f480421(Object []i) {
    double p = Double.NaN;
    if (i[5] == null) {
      p = 0;
    } else if (((Double) i[5]).doubleValue() <= 53.0) {
    p = WekaClassifier.N351037b22(i);
    } else if (((Double) i[5]).doubleValue() > 53.0) {
    p = WekaClassifier.N134fd23324(i);
    } 
    return p;
  }
  static double N351037b22(Object []i) {
    double p = Double.NaN;
    if (i[14] == null) {
      p = 2;
    } else if (((Double) i[14]).doubleValue() <= 8.0) {
      p = 2;
    } else if (((Double) i[14]).doubleValue() > 8.0) {
    p = WekaClassifier.N3bbb81f023(i);
    } 
    return p;
  }
  static double N3bbb81f023(Object []i) {
    double p = Double.NaN;
    if (i[19] == null) {
      p = 0;
    } else if (((Double) i[19]).doubleValue() <= 3.0) {
      p = 0;
    } else if (((Double) i[19]).doubleValue() > 3.0) {
      p = 2;
    } 
    return p;
  }
  static double N134fd23324(Object []i) {
    double p = Double.NaN;
    if (i[9] == null) {
      p = 0;
    } else if (((Double) i[9]).doubleValue() <= 30.15) {
      p = 0;
    } else if (((Double) i[9]).doubleValue() > 30.15) {
      p = 1;
    } 
    return p;
  }
  static double N5d711c2c25(Object []i) {
    double p = Double.NaN;
    if (i[19] == null) {
      p = 0;
    } else if (((Double) i[19]).doubleValue() <= 3.0) {
    p = WekaClassifier.N2cf0bca126(i);
    } else if (((Double) i[19]).doubleValue() > 3.0) {
      p = 0;
    } 
    return p;
  }
  static double N2cf0bca126(Object []i) {
    double p = Double.NaN;
    if (i[14] == null) {
      p = 2;
    } else if (((Double) i[14]).doubleValue() <= 2.0) {
      p = 2;
    } else if (((Double) i[14]).doubleValue() > 2.0) {
    p = WekaClassifier.N70f0051327(i);
    } 
    return p;
  }
  static double N70f0051327(Object []i) {
    double p = Double.NaN;
    if (i[11] == null) {
      p = 2;
    } else if (((Double) i[11]).doubleValue() <= 29.62) {
      p = 2;
    } else if (((Double) i[11]).doubleValue() > 29.62) {
    p = WekaClassifier.N1ddd5c5228(i);
    } 
    return p;
  }
  static double N1ddd5c5228(Object []i) {
    double p = Double.NaN;
    if (i[21] == null) {
      p = 2;
    } else if (((Double) i[21]).doubleValue() <= 210.0) {
    p = WekaClassifier.N2fd81acf29(i);
    } else if (((Double) i[21]).doubleValue() > 210.0) {
      p = 0;
    } 
    return p;
  }
  static double N2fd81acf29(Object []i) {
    double p = Double.NaN;
    if (i[11] == null) {
      p = 2;
    } else if (((Double) i[11]).doubleValue() <= 30.18) {
      p = 2;
    } else if (((Double) i[11]).doubleValue() > 30.18) {
      p = 0;
    } 
    return p;
  }
  static double N14c8249330(Object []i) {
    double p = Double.NaN;
    if (i[7] == null) {
      p = 0;
    } else if (((Double) i[7]).doubleValue() <= 67.0) {
      p = 0;
    } else if (((Double) i[7]).doubleValue() > 67.0) {
    p = WekaClassifier.N5fd9398d31(i);
    } 
    return p;
  }
  static double N5fd9398d31(Object []i) {
    double p = Double.NaN;
    if (i[19] == null) {
      p = 1;
    } else if (((Double) i[19]).doubleValue() <= 3.0) {
      p = 1;
    } else if (((Double) i[19]).doubleValue() > 3.0) {
    p = WekaClassifier.N2e51892432(i);
    } 
    return p;
  }
  static double N2e51892432(Object []i) {
    double p = Double.NaN;
    if (i[21] == null) {
      p = 2;
    } else if (((Double) i[21]).doubleValue() <= 222.0) {
      p = 2;
    } else if (((Double) i[21]).doubleValue() > 222.0) {
      p = 0;
    } 
    return p;
  }
  static double N6b02b23d33(Object []i) {
    double p = Double.NaN;
    if (i[10] == null) {
      p = 4;
    } else if (((Double) i[10]).doubleValue() <= 29.75) {
      p = 4;
    } else if (((Double) i[10]).doubleValue() > 29.75) {
    p = WekaClassifier.N7e03f9ad34(i);
    } 
    return p;
  }
  static double N7e03f9ad34(Object []i) {
    double p = Double.NaN;
    if (i[21] == null) {
      p = 2;
    } else if (((Double) i[21]).doubleValue() <= 194.0) {
    p = WekaClassifier.N36fd0d7d35(i);
    } else if (((Double) i[21]).doubleValue() > 194.0) {
      p = 0;
    } 
    return p;
  }
  static double N36fd0d7d35(Object []i) {
    double p = Double.NaN;
    if (i[19] == null) {
      p = 1;
    } else if (((Double) i[19]).doubleValue() <= 6.0) {
    p = WekaClassifier.N1f80a5bf36(i);
    } else if (((Double) i[19]).doubleValue() > 6.0) {
      p = 2;
    } 
    return p;
  }
  static double N1f80a5bf36(Object []i) {
    double p = Double.NaN;
    if (i[16] == null) {
      p = 2;
    } else if (((Double) i[16]).doubleValue() <= 2.0) {
      p = 2;
    } else if (((Double) i[16]).doubleValue() > 2.0) {
    p = WekaClassifier.N3701aec137(i);
    } 
    return p;
  }
  static double N3701aec137(Object []i) {
    double p = Double.NaN;
    if (i[17] == null) {
      p = 0;
    } else if (((Double) i[17]).doubleValue() <= 19.0) {
      p = 0;
    } else if (((Double) i[17]).doubleValue() > 19.0) {
      p = 1;
    } 
    return p;
  }
}
