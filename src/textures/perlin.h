//
// Created by Johan Solbakken on 25/03/2022.
//

#ifndef RAYTRACER_PERLIN_H
#define RAYTRACER_PERLIN_H

#include "common/core.h"
#include <cmath>

namespace perlin
{
    class Perlin
    {
    public:
        Perlin() {
            m_RanVec = new Vec3[s_PointCount];
            for(int i = 0; i < s_PointCount; i++)
            {
                m_RanVec[i] = unit_vector(Vec3::Random(-1, 1));
            }

            m_PermX = PerlinGeneratePerm();
            m_PermY = PerlinGeneratePerm();
            m_PermZ = PerlinGeneratePerm();
        }

        ~Perlin()
        {
            delete[] m_RanVec;
            delete[] m_PermX;
            delete[] m_PermY;
            delete[] m_PermZ;
        }

        double Noise(const Point3& point) const
        {
            auto u = point.x() - floor(point.x());
            auto v = point.y() - floor(point.y());
            auto w = point.z() - floor(point.z());

            u = u*u*(3-2*u);
            v = v*v*(3-2*v);
            w = w*w*(3-2*w);

            auto i = static_cast<int>(floor(point.x()));
            auto j = static_cast<int>(floor(point.y()));
            auto k = static_cast<int>(floor(point.z()));

            Vec3 c[2][2][2];

            for (int di = 0; di < 2; di++)
            {
                for (int dj = 0; dj < 2; dj++)
                {
                    for (int dk = 0; dk < 2; dk++)
                    {
                        c[di][dj][dk] = m_RanVec[
                                m_PermX[(i+di) & 255] ^
                                m_PermY[(j+dj) & 255] ^
                                m_PermZ[(k+dk) & 255]
                                ];
                    }
                }
            }

            return PerlinIterp(c, u, v, w);
        }

        double Turb(const Point3& point, int depth=7) const
        {
            auto accum = 0.0;
            auto temp_point = point;
            auto weight = 1.0;

            for (int i = 0; i < depth; i++)
            {
                accum += weight * Noise(temp_point);
                weight *= 0.5;
                temp_point *= 2;
            }

            return fabs(accum);
        }

    private:
        static int* PerlinGeneratePerm() {
            auto p = new int[s_PointCount];

            for (int i = 0; i < Perlin::s_PointCount; i++)
                p[i] = i;

            Permute(p, s_PointCount);

            return p;
        }

        static void Permute(int* p, int n) {
            for (int i = n-1; i > 0; i--) {
                int target = random_int(0, i);
                int tmp = p[i];
                p[i] = p[target];
                p[target] = tmp;
            }
        }

        static double TrilinearInterp(double c[2][2][2], double u, double v, double w) {
            auto accum = 0.0;
            for (int i=0; i < 2; i++)
                for (int j=0; j < 2; j++)
                    for (int k=0; k < 2; k++)
                        accum += (i*u + (1-i)*(1-u))*
                                 (j*v + (1-j)*(1-v))*
                                 (k*w + (1-k)*(1-w))*c[i][j][k];

            return accum;
        }

        static double PerlinIterp(Vec3 c[2][2][2], double u, double v, double w)
        {
            auto uu = u*u*(3-2*u);
            auto vv = v*v*(3-2*v);
            auto ww = w*w*(3-2*w);
            auto accum = 0.0;

            for (int i=0; i < 2; i++)
                for (int j=0; j < 2; j++)
                    for (int k=0; k < 2; k++) {
                        Vec3 weight_v(u-i, v-j, w-k);
                        accum += (i*uu + (1-i)*(1-uu))
                                 * (j*vv + (1-j)*(1-vv))
                                 * (k*ww + (1-k)*(1-ww))
                                 * dot(c[i][j][k], weight_v);
                    }

            return accum;
        }

    private:
        static const int s_PointCount = 256;
        Vec3* m_RanVec;
        int* m_PermX;
        int* m_PermY;
        int* m_PermZ;
    };
}

#endif //RAYTRACER_PERLIN_H
