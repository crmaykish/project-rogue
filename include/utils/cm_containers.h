#ifndef CM_CONTAINERS_H
#define CM_CONTAINERS_H

#include <map>

namespace cm
{
    // TODO: this class could probably be a normal map with a Point as the key
    template <class T>
    class CoordinateMap
    {
    private:
        std::map<int, std::map<int, T>> container;

    public:
        bool Contains(int x, int y)
        {
            if (container.find(x) == container.end())
            {
                return false;
            }

            if (container.at(x).find(y) == container.at(x).end())
            {
                return false;
            }

            return true;
        }

        T *At(int x, int y)
        {
            if (Contains(x, y))
            {
                return &(container.at(x).at(y));
            }

            return nullptr;
        }

        void Insert(int x, int y, T p)
        {
            if (container.find(x) == container.end())
            {
                // create the second map
                container.insert({x, std::map<int, T>()});
            }

            container.at(x).insert({y, p});
        }
    };

} // namespace cm

#endif /* CM_CONTAINERS_H */
