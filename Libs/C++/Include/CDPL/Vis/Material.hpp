/* 
 * Material.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Definition of the class CDPL::Vis::Material.
 */

#ifndef CDPL_VIS_MATERIAL_HPP
#define CDPL_VIS_MATERIAL_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Color.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Defines material properties of Vis::Object3D instances.
         *
         * A color vector for each of the Phong lighting's components is defined (alpha channel will be inored):
         * The ambient component defines what color the surface reflects under ambient lighting. This is usually 
         * the same as the surface's color. The diffuse component defines the color of the surface under diffuse lighting. 
         * The diffuse color is (just like ambient lighting) usually set to the desired surface's color. The specular component sets 
         * the color of the specular highlight on the surface (or possibly even reflect a surface-specific color). 
         * Lastly, the shininess impacts the scattering/radius of the specular highlight. For transparent materials a transparency
         * in the range \e 0.0 to \e 1.0 can be specified where a value of \e 0.0 represents a completely opaque material.
         *
         * \since 1.3
         */
        class CDPL_VIS_API Material
        {

          public:
            /**
             * \brief Constructs an new \c %Material instance with the specified properties.
             * \param amb_color The ambient color component.
             * \param amb_factor The scaling factor to use for calculating the ambient from the diffuse color component.
             * \param diff_color The diffuse color component.
             * \param spec_color The specular color component.
             * \param shininess The shininess value.
             * \param transp The transparency value.
             */
            Material(const Color& amb_color, double amb_factor, const Color& diff_color, const Color& spec_color, double shininess, double transp = 0.0);

            /**
             * \brief Constructs an new \c %Material instance with the specified properties.
             * \param amb_factor The scaling factor to use for calculating the ambient from the diffuse color component.
             * \param diff_color The diffuse color component.
             * \param spec_color The specular color component.
             * \param shininess The shininess value.
             * \param transp The transparency value.
             */
            Material(double amb_factor, const Color& diff_color, const Color& spec_color, double shininess, double transp = 0.0);

            /**
             * \brief Sets the ambient color component.
             * \param color The ambient color component.
             */
            void setAmbientColor(const Color& color);

            /**
             * \brief Returns the ambient color component.
             * \return The ambient color component.
             */
            const Color& getAmbientColor() const;

            /**
             * \brief Sets the scaling factor to use for calculating the ambient from the diffuse color component.
             * \param factor The scaling factor in the range [0, 1].
             */
            void setAmbientFactor(double factor);

            /**
             * \brief Returns the scaling factor used for calculating the ambient from the diffuse color component.
             * \return The scaling factor.
             */
            double getAmbientFactor() const;
            
            /**
             * \brief Sets the diffuse color component.
             * \param color The diffuse color component.
             */
            void setDiffuseColor(const Color& color);

            /**
             * \brief Returns the diffuse color component.
             * \return The diffuse color component.
             */
            const Color& getDiffuseColor() const;

            /**
             * \brief Sets the specular color component.
             * \param color The specular color component.
             */
            void setSpecularColor(const Color& color);

            /**
             * \brief Returns the specular color component.
             * \return The specular color component.
             */
            const Color& getSpecularColor() const;

            /**
             * \brief Sets the shininess of the material.
             * \param shininess The shininess value in the range [0, 1].
             */
            void setShininess(double shininess);

            /**
             * \brief Returns the shininess of the material.
             * \return The shininess value.
             */
            double getShininess() const;

            /**
             * \brief Sets the transparency of the material.
             * \param transp The transparency value in the range [0, 1].
             */
            void setTransparency(double transp);

            /**
             * \brief Returns the transparency of the material.
             * \return The transparency value.
             */
            double getTransparency() const;
            
            /**
             * \brief Equality comparison operator.
             * \param material The other \c %Material object to be compared with.
             * \return \c true if the style and color attributes compare equal, and \c false otherwise.
             */
            bool operator==(const Material& material) const;

            /**
             * \brief Inequality comparison operator.
             *
             * The result is equivalent to <tt>!(*this == material)</tt>.
             *
             * \param material The other \c %Material object to be compared with.
             * \return \c true if either the style or the color attributes compare non-equal, and \c false otherwise.
             */
            bool operator!=(const Material& material) const;

          private:
            Color  ambient;
            double ambientFactor;
            Color  diffuse;
            Color  specular;
            double shininess;
            double transparency;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_MATERIAL_HPP
