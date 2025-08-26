#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief Defines material properties of Vis.Object3D instances.
# 
# A color vector for each of the Phong lighting's components is defined (alpha channel will be inored): The ambient component defines what color the surface reflects under ambient lighting. This is usually the same as the surface's color. The diffuse component defines the color of the surface under diffuse lighting. The diffuse color is (just like ambient lighting) usually set to the desired surface's color. The specular component sets the color of the specular highlight on the surface (or possibly even reflect a surface-specific color). Lastly, the shininess impacts the scattering/radius of the specular highlight. For transparent materials a transparency in the range <em>0.0</em> to <em>1.0</em> can be specified where a value of <em>0.0</em> represents a completely opaque material.
# 
# \since 1.3
# 
class Material(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \e %Material instance \a material.
    # \param material The \e %Material instance to copy.
    # 
    def __init__(material: Material) -> None: pass

    ##
    # \brief Constructs an new <tt>Material</tt> instance with the specified properties.
    # 
    # \param amb_color The ambient color component.
    # \param diff_color The diffuse color component.
    # \param spec_color The specular color component.
    # \param shininess The shininess value.
    # \param transp The transparency value.
    # 
    def __init__(amb_color: Color, diff_color: Color, spec_color: Color, shininess: float, transp: float = 1.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %Material instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Material instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %Material instance \a material.
    # \param material The \c %Material instance to copy.
    # \return \a self
    # 
    def assign(material: Material) -> Material: pass

    ##
    # \brief Returns the ambient color component.
    # 
    # \return The ambient color component.
    # 
    def getAmbientColor() -> Color: pass

    ##
    # \brief Sets the ambient color component.
    # 
    # \param color The ambient color component.
    # 
    def setAmbientColor(color: Color) -> None: pass

    ##
    # \brief Returns the diffuse color component.
    # 
    # \return The diffuse color component.
    # 
    def getDiffuseColor() -> Color: pass

    ##
    # \brief Sets the diffuse color component.
    # 
    # \param color The diffuse color component.
    # 
    def setDiffuseColor(color: Color) -> None: pass

    ##
    # \brief Returns the specular color component.
    # 
    # \return The specular color component.
    # 
    def getSpecularColor() -> Color: pass

    ##
    # \brief Sets the specular color component.
    # 
    # \param color The specular color component.
    # 
    def setSpecularColor(color: Color) -> None: pass

    ##
    # \brief Returns the transparency of the material.
    # 
    # \return The transparency value.
    # 
    def getTransparency() -> float: pass

    ##
    # \brief Sets the transparency of the material.
    # 
    # \param transp The transparency value.
    # 
    def setTransparency(transp: float) -> None: pass

    ##
    # \brief Returns the shininess of the material.
    # 
    # \return The shininess value.
    # 
    def getShininess() -> float: pass

    ##
    # \brief Sets the shininess of the material.
    # 
    # \param shininess The shininess value.
    # 
    def setShininess(shininess: float) -> None: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param material The other <tt>Material</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if the style and color attributes compare equal, and <tt>False</tt> otherwise.
    # 
    def __eq__(material: Material) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == material)</tt>.
    # 
    # \param material The other <tt>Material</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if either the style or the color attributes compare non-equal, and <tt>False</tt> otherwise.
    # 
    def __ne__(material: Material) -> bool: pass

    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    ambient = property(getAmbient, setAmbient)

    ##
    # \brief FIXME!
    #
    diffuse = property(getDiffuse, setDiffuse)

    ##
    # \brief FIXME!
    #
    specular = property(getSpecular, setSpecular)

    shininess = property(getShininess, setShininess)

    transparency = property(getTransparency, setTransparency)
