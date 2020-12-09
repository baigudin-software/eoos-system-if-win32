/**
 * @brief Class implements the transport level of OSI model.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_IPC_CLIENT_HPP_
#define SYS_IPC_SERVER_HPP_

#include "sys.IpcBase.hpp"
#include "sys.Fifo.hpp"

#if EOOS_CPP_STANDARD < 2011
#error "C++ language standard less than C++11 is not supported"
#endif

namespace eoos
{
namespace sys
{
    
class IpcServer final : public IpcBase
{
    
public:
    
    /**
     * @brief Constructor.
     *
     * @param dbPath - Path to a dir contains FIFO files.
     */
    explicit IpcServer(const String& dbPath) : IpcBase(dbPath)
    {
        setConstructed( construct() );
    }
    
    /**        
     * @brief Destructor.
     */
    virtual ~IpcServer() noexcept {}

    /**
     * @brief Copy constructor.
     */
    IpcServer(const IpcServer&) = delete;

    /**
     * @brief Move constructor.
     */
    IpcServer(IpcServer&&) = delete;

    /**
     * @brief Copy assignment operator.
     */
    IpcServer& operator=(const IpcServer&) = delete;

    /**
     * @brief Move assignment operator.
     */
    IpcServer& operator=(IpcServer&&) = delete;

    /**
     * @brief Sends data to a client.
     *
     * @param clientId - An IPC Identifier.
     * @param data - Pointer to data.
     * @param size - Size of data in Bytes.
     * @return true if the data sent.
     */
    bool_t send(const IpcId& clientId, const void* const data, std::size_t const size) noexcept try
    {
        if( not isConstructed() )
        {
            return false;
        }
        if( data == NULLPTR || size == 0 )
        {
            return false;
        }
        // Open TX FIFO for transmiting to a client.
        String const txPath {getFilePath(clientId)};
        Fifo txFifo {txPath,
            Fifo::Flag(Fifo::Flag::WRITE
            | Fifo::Flag::BLOCK)
        };
        if( not txFifo.isConstructed() )
        {
            return false;
        }
        // Prepare the packet
        IpcPacket packet {serverId_, clientId};
        bool_t isDone {false};
        isDone = packet.reserve(size);
        if( not isDone )
        {
            return false;
        }
        isDone = packet.emplace(data, size);
        if( not isDone )
        {
            return false;
        }
        // Send the packet
        const void* const packetData {packet.getPacket()};
        std::size_t const packetSize {packet.getPacketSize()};
        std::size_t const sentSize { txFifo.write(packetData, packetSize) };
        return sentSize == packetSize;
    } catch (...) {
        return false;
    }

private:

    /**
     * @brief Gets a reading stream.
     *
     * @return a stream for receiving data.
     */
    api::Read& getReedSrteam() override
    {
        return rxFifo_;
    }

    /**
     * @brief Gets a self IPC Identifier.
     *
     * @return a self IPC Identifier.
     */
    IpcId getIpcId() const override
    {
        return serverId_;
    }

    /**
     * @brief Constructs this object.
     *
     * @return true if this object has been constructed successfully.
     */
    bool_t construct()
    {
        bool_t res {false};
        do{
            if( not isConstructed() )
            {
                break;
            }
            if( rxFifo_.isConstructed() )
            {
                break;
            }
            res = true;
        }while(false);
        return res;
    }

    /**
     * @brief The server IPC Identifier
     */
    IpcId serverId_ {IpcId::getServerId()};
    
    /**
     * @brief RX FIFO for receiving a server response.
     */
    Fifo rxFifo_ {getFilePath(serverId_),
        Fifo::Flag(Fifo::Flag::READ
                 | Fifo::Flag::BLOCK
                 | Fifo::Flag::REMOVE
                 | Fifo::Flag::CREATE)
    };
};

} // namespace sys
} // namespace eoos
#endif // SYS_IPC_CLIENT_HPP_
